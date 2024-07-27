classdef plotter < handle
    %
    %   Class:
    %   adi.plotter
    %
    %   See Also
    %   --------
    %   adi.plot
    %
    %   Note, some channels may be calculated. This program
    %   can't see those calculations so those channels will
    %   look incorrect if recorded
    %
    %   Improvements
    %   ------------
    %   - allow calculated channels
    %   - add scroll bar
    %   - Expose options for printing to file (and any other options)
    %   - Show if "fast plotting" is detected (i.e., is the plotBig library
    %      present)

    properties
        file_path
        h_file
        h_fig
        h_fig_plot
        h_table
        h_record

        %Button to redraw
        h_redraw
        
        %Button to print the study
        h_print_study

        %Name of the loaded file
        h_file_label
        h_fast_plot_enabled
        h_status_label

        n_records
        n_channels
    end

    methods
        function obj = plotter(file_path)

            %                    width height
            CONTROL_PANEL_SIZE = [670 420];


            obj.file_path = file_path;

            obj.h_file = adi.readFile(file_path);

            obj.n_records = obj.h_file.n_records;
            obj.n_channels = obj.h_file.n_channels;

            obj.h_fig = uifigure('Units','pixels');
            obj.h_fig.CloseRequestFcn = @(~,~)obj.closeFigureCallback;
            obj.h_fig.Position(3:4) = CONTROL_PANEL_SIZE;

            items_data = 1:obj.n_records;
            items = arrayfun(@(x) sprintf('record: %d',x),items_data,'un',0);

            %   Layout
            %
            %   ==========================================================
            %   -----  file_name label ---------------
            %
            %   record_select  redraw button  print_file
            %
            %   table
            %   ----------------------------------------------------------
            %   ----------------------------------------------------------
            %   ----------------------------------------------------------
            %   ==========================================================

            [~,file_name] = fileparts(file_path);
            label_text = sprintf('file: %s.adicht',file_name);
            label_width = 350; %CONTROL_PANEL_SIZE(1)-20;
            file_label_bottom = 380;
            obj.h_file_label = uilabel(obj.h_fig,'Text',label_text,'Position',[10 file_label_bottom label_width 20]);

            fast_plot_enabled = ~isempty(which('plotBig'));
            if fast_plot_enabled
                display_text = 'fast plotting enabled';
            else
                display_text = 'slow plotting (missing plotBig lib)';
            end
            fast_plot_width = 200;
            left_bound = CONTROL_PANEL_SIZE(1) - 10 - fast_plot_width;
            obj.h_fast_plot_enabled = uilabel(obj.h_fig,'Text',display_text,'Position',[left_bound file_label_bottom fast_plot_width 20]);

            obj.h_status_label = uilabel(obj.h_fig,'Text','','Position',[10 350 200 20]);

            obj.h_record = uidropdown(obj.h_fig,'Items',items,...
                'ItemsData',items_data,'Position',[10 320 100 20]);

            obj.h_redraw = uibutton(obj.h_fig,'Text','redraw','Position',[120 320 100 20]);
            obj.h_redraw.ButtonPushedFcn = @(~,~)obj.redrawCallback;

            obj.h_print_study = uibutton(obj.h_fig,'Text','print study','Position',[240 320 100 20]);
            obj.h_print_study.ButtonPushedFcn = @(~,~)obj.printStudyCallback;


            %h_print_study

            t = table();
            t.enabled = true(obj.n_channels,1);
            t.name = obj.h_file.channel_names(:);
            t.y_min = -1*ones(obj.n_channels,1);
            t.y_max = ones(obj.n_channels,1);
            t.y_auto = true(obj.n_channels,1);
            scale = floor(100/obj.n_channels);
            t.pct = scale*ones(obj.n_channels,1);
            t.pct_auto = true(obj.n_channels,1);
            temp = categorical(["none","low pass","high pass"]);
            t.filter = repmat(temp(1),height(t),1);
            t.cutoff = 100*ones(obj.n_channels,1);
            t.order  = ones(obj.n_channels,1);

            obj.h_table = uitable(obj.h_fig,'Data',t,'Units','pixels','Position',[10 10 650 300]);
            obj.h_table.ColumnEditable = true;
            %Adjust widths
            %1 enabled
            %2 name
            %3 y_min
            %4 y_max
            %5 y_auto
            %6 pct
            %7 pct_auto
            %8 filter
            %9 cutoff
            %10 order
            %                          1  2   3  4  5  6  7  8  9  0
            obj.h_table.ColumnWidth = {60 140 50 50 60 40 65 65 50 50};

            obj.h_table.CellEditCallback = @obj.tableCallback;

            obj.plotRecord(1);
        end

        function redrawCallback(obj)
            record_id = obj.h_record.Value;
            obj.plotRecord(record_id);
        end
        function tableCallback(obj,ev,src)
            %
            %   - enabled change - hide or show plot
            %   - name change - update y-axis
            %   - y_min
            %   - y_max
            %   - y_auto
            %
            %   Really, any change, replot

            %TODO: Need to handle scaling
            %
            %   Channel hidden - take into account with scaling
            %

            %{
                   Indices: [6 3]
            DisplayIndices: [6 3]
              PreviousData: -1
                  EditData: '0'
                   NewData: 0
                     Error: []
                    Source: [1×1 Table]
                 EventName: 'CellEdit'
            %}

            %Columns
            %---------------
            %1) enabled
            %2) name
            %3) y_min
            %4) y_max
            %5) y_auto
            %6) pct
            %7) pct_auto

            column_index = src.Indices(2);
            row_index = src.Indices(1);

            if column_index == 3 || column_index == 4
                obj.h_table.Data.y_auto(row_index) = false;
            end

            if column_index == 6 || column_index == 7 || column_index == 1
                %Reprocess percentages

                %If changing pct, set auto to false
                if column_index == 6
                    obj.h_table.Data.pct_auto(row_index) = false;
                end

                pct_auto = obj.h_table.Data.pct_auto;

                enabled_mask = obj.h_table.Data.enabled;
                pct_auto_mask = pct_auto & enabled_mask;
                pct_man_mask  = ~pct_auto & enabled_mask;

                pct = obj.h_table.Data.pct;
                pct(~enabled_mask) = 0;

                total_pct_non_auto = sum(pct(pct_man_mask));
                if total_pct_non_auto >= 100
                    %Note below we've ensured this disables
                    %plotting of this channel
                    pct(pct_auto_mask) = 0;
                else
                    remaining_pct = 100 - total_pct_non_auto;
                    n_pct_auto = sum(pct_auto_mask);
                    pct_each = floor(remaining_pct/n_pct_auto);
                    pct(pct_auto_mask) = pct_each;
                end
                obj.h_table.Data.pct = pct;
            end

        end
        function closeFigureCallback(obj)
            try
                delete(obj.h_fig)
            end
            try
                delete(obj.h_fig_plot)
            end
        end
        function s = plotRecord(obj,record_id,varargin)
            %
            %
            %   TODO: Update documentation

            s = struct;

            %Note, we don't really expose these options yet ...
            in.link_x = true;
            in.time_range = [];
            in.axes = [];
            in.channel_spacing = 0.01;
            in.top_border = 0.01;
            in.left_border = 0.05;
            in.right_border = 0.02;
            in.bottom_border = 0.05;
            in.clear_figure = true;
            in = adi.sl.in.processVarargin(in,varargin);

            obj.h_status_label.Text = 'plotting';

            obj.h_fig_plot = figure(1);
            obj.h_fig_plot.HandleVisibility = 'off';
            obj.h_fig_plot.CloseRequestFcn = @(~,~)obj.closeFigureCallback;
            if in.clear_figure
                clf(obj.h_fig_plot)
            end

            t = obj.h_table.Data;
            enabled_mask = t.enabled & t.pct > 0;
            enabled_channel_indices = find(enabled_mask);

            n_channels2 = length(enabled_channel_indices);

            colors = colororder(obj.h_fig_plot);
            if n_channels2 > size(colors,1)
                colors = repmat(colors,ceil(n_channels2/ceil(size(colors,1))),1);
            end

            h_axes = cell(1,n_channels2);
            empty_plot_mask = false(1,n_channels2);
            for i = 1:n_channels2
                if isempty(in.axes)
                    h_axes{i} = subplot(n_channels2,1,i,'Parent',obj.h_fig_plot);
                else
                    h_axes{i} = in.axes(i);
                end
                hold(h_axes{i},'on')

                cur_channel_index = enabled_channel_indices(i);
                channel_name = obj.h_table.Data.name{cur_channel_index};
                obj.h_status_label.Text = sprintf('Loading %d/%d, %s',i,n_channels2,channel_name);
                drawnow

                if ~isempty(in.time_range)
                    time_options = {'time_range',in.time_range};
                else
                    time_options = {};
                end

                if isempty(which('plotBig'))
                    [data,time] = obj.h_file.getChannelData(cur_channel_index,...
                        record_id,'datetime_out',true,'return_object',false,...
                        time_options{:});
                else
                    [data,time] = obj.h_file.getChannelData(cur_channel_index,...
                        record_id,'datetime_out',true,'return_object',false,...
                        'time_as_object',true,time_options{:});
                end

                if isempty(data)
                    %do nothing
                    empty_plot_mask(i) = true;
                else
                    %Filter if needed
                    %------------------------------------------
                    %["none","low pass","high pass"]
                    switch t.filter(cur_channel_index)
                        case 'none'
                        case {'low pass' 'high pass'}
                            filter_cutoff = t.cutoff(cur_channel_index);
                            filter_order = t.order(cur_channel_index);
                            if isempty(which('plotBig'))
                                fs = time(2)-time(1);
                            else
                                fs = time.fs;
                            end
                            half_fs = 0.5*fs;
                            Wn = filter_cutoff/half_fs;
                            if t.filter == "high pass"
                                filt_type = 'high';
                            else
                                filt_type = 'low';
                            end
                            [B,A] = butter(filter_order,Wn,filt_type);
                            data = filtfilt(B,A,data);
                    end

                    %The actual plotting
                    %-------------------------------------------------
                    if isempty(which('plotBig'))
                        plot(time,data,'Color',colors(i,:));
                    else
                        plotBig(h_axes{i},time,data,'Color',colors(i,:))
                    end
                    axis(h_axes{i},'tight')
                end

                %Adding y-label
                %------------------------
                channel_name = t.name{cur_channel_index};
                units = obj.h_file.channel_specs(cur_channel_index).units{record_id};
                y_label = sprintf('%s (%s)',channel_name,units);
                ylabel(h_axes{i},y_label)
            end

            obj.h_status_label.Text = 'Done loading, working on layout';
            drawnow

            h_axes = [h_axes{:}];

            %Linking axes
            %-------------------------------------------------------
            if in.link_x
                %Note, we offer to disable this in case plotting multiple
                %records ...

                %   This turns out to be tough if data are missing
                valid_axes = h_axes(~empty_plot_mask);
                xlim_temp = vertcat(valid_axes.XLim);
                x1 = min(xlim_temp(:,1));
                x2 = max(xlim_temp(:,2));
                invalid_axes = h_axes(empty_plot_mask);
                for i = 1:length(invalid_axes)
                    %https://www.mathworks.com/matlabcentral/answers/1656100-pre-set-axis-limit-to-datetime
                    %
                    %   :/
                    invalid_axes(i).XAxis = matlab.graphics.axis.decorator.DatetimeRuler;
                    invalid_axes(i).XLim = [x1 x2];
                end

                linkaxes(h_axes,'x');
            end

            %Turn off xticks and labels for 1:(n-1)
            %--------------------------------------------------------
            for i = 1:length(h_axes)-1
                h_axes(i).XLabel.String = "";
                h_axes(i).XTickLabels = [];
            end

            %Resizing ...
            %--------------------------------------------------------
            pct = t.pct(enabled_mask);
            %rescale to 0.03 to 0.97
            %
            %   let's add 0.01 for every gap
            %
            %   - so 0.94 total

            pct_total = 1 - in.top_border - in.bottom_border;
            pct = pct./sum(pct)*(pct_total - n_channels2*in.channel_spacing);
            b = in.bottom_border;
            w = 1 - in.left_border - in.right_border;
            for i = length(h_axes):-1:1
                h_axes(i).Position(1) = in.left_border;
                h_axes(i).Position(2) = b;
                h_axes(i).Position(3) = w;
                h_axes(i).Position(4) = pct(i);
                b = b + pct(i) + 0.01;
            end

            %YLim setting
            %----------------------------------------------------------
            for i = 1:n_channels2
                cur_row = enabled_channel_indices(i);
                ylim = h_axes(i).YLim;
                if t.y_auto(cur_row)
                    %If y_auto, set y_min and y_max in table
                    %obj.h_table.Data.y_min(cur_row) = ylim(1);
                    %obj.h_table.Data.y_max(cur_row) = ylim(2);
                else
                    %else, set ylim
                    ylim(1) = t.y_min(cur_row);
                    ylim(2) = t.y_max(cur_row);
                    h_axes(i).YLim = ylim;
                end
            end

            %Comment drawing
            %----------------------------------------------------------
            obj.h_status_label.Text = 'Processing comments';
            drawnow
            comments = obj.h_file.getAllComments('output','table','use_datetime',true);
            comments = comments(comments.record == record_id,:);
            if ~isempty(in.time_range)
                c_times = comments.absolute_time;
                mask = c_times >= in.time_range(1) & c_times <= in.time_range(2);
                comments = comments(mask,:);
            end
            if ~isempty(comments)
                for i = 1:n_channels2
                    %text
                    %id
                    %absolute_time
                    for j = 1:height(comments)
                        comment = comments(j,:);
                        x = [comment.absolute_time comment.absolute_time];
                        y = h_axes(i).YLim;
                        line_handle = plot(h_axes(i),x,y,':k','YLimInclude','off');
                        if i == n_channels2
                            cur_line = line_handle;
                            temp_x = get(cur_line,'XData');
                            temp_y = get(cur_line,'YData');
                            display_string = sprintf('%d) %s',comment.id,comment.text);
                            text(temp_x(1),temp_y(1),display_string,...
                                'rotation',90,'HorizontalAlignment','left',...
                                'VerticalAlignment','bottom',...
                                'parent',h_axes(i));
                        end
                    end
                end
            end

            obj.h_status_label.Text = '';

            s.h_axes = h_axes;
        end
    end

    methods
        function printStudyCallback(obj,varargin)
            in.width_per_slide = 20*60;
            in.overlap_width = 0; %2*60;
            in.print_size_units = 'inches';
            in.print_size = [11 8.5];
            in.plot_record_break = true;
            in = adi.sl.in.processVarargin(in,varargin);

            %Call to external file ...
            h__printFile(obj,in);
        end
    end
end


function h__printFile(obj,in)
%
%
%   This is called from

%Options
%---------------------
%- Ordering
%- % to show
%- width per slide (seconds)
%- print size
%- overlap
%- which channels to plot
%- need plot height info

% in.width_per_slide = 20*60;
% in.overlap_width = 2*60;
% in.print_size = [8.5 11];
% in = adi.sl.in.processVarargin(in,varargin);

f = obj.h_file;

%# of active channels
%duration of all records


%Need to go from absolute time to
record_starts = NaT(1,f.n_records);
record_ends = NaT(1,f.n_records);
for i = 1:f.n_records
    record_starts(i) = f.records(i).data_start_datetime;
    record_ends(i) = record_starts(i) + seconds(f.records(i).duration);
end

% total_duration_s = record_ends(end)-record_starts(1);

step_size = seconds(in.width_per_slide - in.overlap_width);
starts = record_starts(1):step_size:record_ends(end);
stops = starts + seconds(in.width_per_slide);

n_records = f.n_records;
n_pages = length(starts);

n_channels = f.n_channels;

%Scaling
%---------------------------------------------
%
%
%   This is only needed if no scaling is presented

t = obj.h_table.Data;

obj.h_status_label.Text = 'retrieving y-limits for channels';

% chan_data = cell(1,n_records);
chan_min = NaN(n_channels,1);
chan_max = NaN(n_channels,1);
for i = 1:n_channels
    if t.y_auto(i)
        for j = 1:n_records
            temp = f.getChannelData(i,j,'return_object',false);
            if ~isempty(temp)
                chan_min(i) = min(chan_min(i),min(temp));
                chan_max(i) = max(chan_max(i),max(temp));
            end
        end
    else
        chan_min(i) = t.y_min(i);
        chan_max(i) = t.y_max(i);
    end
end

n_digits_formatting = sprintf('0%d',length(sprintf('%d',n_pages)));

all_file_paths = cell(1,n_pages);

for i = 1:n_pages
    message = sprintf('Page: %d/%d\n',i,n_pages);
    n_chars_message = length(message);
    fprintf('%s',message);
    page_id = i;
    mask1 = record_starts >= starts(i) & record_starts <= stops(i);
    mask2 = record_ends >= starts(i) & record_ends <= stops(i);
    mask3 = record_starts <= starts(i) & record_ends >= stops(i);
    records_include = find(mask1 | mask2 | mask3);

    if isempty(records_include)
        continue
    end

    %fprintf('%d, %s\n',i,mat2str(records_include));

    for j = 1:length(records_include)

        cur_record = records_include(j);
        r_t1 = record_starts(cur_record);
        r_t2 = record_ends(cur_record);
        overlap_start = max(starts(i), r_t1);
        overlap_stop = min(stops(i), r_t2);
        time_range = [overlap_start,overlap_stop];

        clear_figure = j == 1;

        if j == 1
            axes = [];
        else
            axes = s.h_axes;
        end

        if j == length(records_include)
            link_x = true;
        else
            link_x = false;
        end

        s = obj.plotRecord(cur_record,'time_range',time_range,...
            'clear_figure',clear_figure,'axes',axes,'link_x',link_x);
    end

    %Do this after adjustments based on the data
    if in.plot_record_break
        for j = 1:length(records_include)
            %This was to plot the start of a block ...
            %-----------------------------------------------
            %We could make this optional ...
            cur_record = records_include(j);
            r_t1 = record_starts(cur_record);
            r_t2 = record_ends(cur_record);
            overlap_start = max(starts(i), r_t1);
            overlap_stop = min(stops(i), r_t2);
            if r_t1 >= overlap_start && ...
                    r_t1 <= overlap_stop
                n_channels = length(s.h_axes);
                for k = 1:n_channels
                    ax = s.h_axes(k);
                    ylim = ax.YLim;
                    line_handle = plot(ax,[r_t1 r_t1],ylim,'k');
                    if k == n_channels
                        cur_line = line_handle;
                        temp_x = get(cur_line,'XData');
                        temp_y = get(cur_line,'YData');
                        display_string = sprintf('Block %d',cur_record);
                        text(temp_x(1),temp_y(1),display_string,...
                            'rotation',90,'HorizontalAlignment','left',...
                            'VerticalAlignment','bottom',...
                            'parent',ax);
                    end
                end
            end
        end
    end

    obj.h_fig_plot.Units = in.print_size_units;
    obj.h_fig_plot.Position(3:4) = in.print_size;

    [file_root,file_name] = fileparts(obj.file_path);
    save_root = fullfile(file_root,'printed_files');

    if ~exist(save_root,'dir')
        mkdir(save_root)
    end

    save_file_name = sprintf(['%s_%' n_digits_formatting 'd.pdf'],file_name,page_id);
    save_path = fullfile(save_root,save_file_name);

    adi.sl.plot.export.saveAsPDF(obj.h_fig_plot,'file_path',save_path);

    all_file_paths{i} = save_path;

    %Adjust everything and print
    %   - page size
    %   - tighten spacing
    %   - where to save
    %       - by default save to
    %   - add title

    %https://www.mathworks.com/matlabcentral/answers/372643-is-it-possible-to-rewrite-update-a-printed-line
    ASCII_BKSP_CHAR = 8;
    message = char(repmat(ASCII_BKSP_CHAR,1,n_chars_message));
    fprintf('%s',message)
end

mask = cellfun('isempty',all_file_paths);
all_file_paths(mask) = [];

save_file_name = sprintf('%s.pdf',file_name);
final_save_path = fullfile(save_root,save_file_name);

adi.sl.io.mergePDFs(all_file_paths,final_save_path,'delete_inputs',true);


end

