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

    properties
        h_file
        h_fig
        h_fig_plot
        h_table
        h_record
        h_redraw
        h_file_label
        h_status_label

        n_records
        n_channels
    end

    methods
        function obj = plotter(file_path)

            %Two things:
            %
            %table
            %
            %plot

            obj.h_file = adi.readFile(file_path);

            obj.n_records = obj.h_file.n_records;
            obj.n_channels = obj.h_file.n_channels;

            obj.h_fig = uifigure('Units','pixels');
            obj.h_fig.Position(3:4) = [620 420];

            items_data = 1:obj.n_records;
            items = arrayfun(@(x) sprintf('record: %d',x),items_data,'un',0);

            %   -----  file_name label ---------------
            %   
            %   record_select      redraw button
            %
            %   table

            [~,file_name] = fileparts(file_path);
            label_text = sprintf('file: %s.adicht',file_name);
            obj.h_file_label = uilabel(obj.h_fig,'Text',label_text,'Position',[10 380 200 20]);
            obj.h_status_label = uilabel(obj.h_fig,'Text','','Position',[10 350 200 20]);

            obj.h_record = uidropdown(obj.h_fig,'Items',items,...
                'ItemsData',items_data,'Position',[10 320 100 20]);

            obj.h_redraw = uibutton(obj.h_fig,'Text','redraw','Position',[120 320 100 20]);
            obj.h_redraw.ButtonPushedFcn = @(~,~)obj.redrawCallback; 

            t = table();
            t.enabled = true(obj.n_channels,1);
            t.name = obj.h_file.channel_names(:);
            t.y_min = -1*ones(obj.n_channels,1);
            t.y_max = ones(obj.n_channels,1);
            t.y_auto = true(obj.n_channels,1);
            scale = floor(100/obj.n_channels);
            t.pct = scale*ones(obj.n_channels,1);
            t.pct_auto = true(obj.n_channels,1);

            obj.h_table = uitable(obj.h_fig,'Data',t,'Units','pixels','Position',[10 10 600 300]);
            obj.h_table.ColumnEditable = true;
            %Adjust widths
            %obj.h_table.

            obj.h_table.CellEditCallback = @obj.tableCallback;

            obj.plotRecord(1)
        end
        function redrawCallback(obj)
            record_id = obj.h_record.Value;
            plotRecord(obj,record_id)
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

            keyboard



        end
        function closeFigureCallback(obj)
            
            try
                delete(obj.h_fig)
            end

            try
                delete(obj.h_fig_plot)
            end
        end
        function plotRecord(obj,record_id)

            %which channels?

            obj.h_status_label.Text = 'plotting';

            obj.h_fig_plot = figure(1);
            obj.h_fig_plot.HandleVisibility = 'off';
            obj.h_fig_plot.CloseRequestFcn = @(~,~)obj.closeFigureCallback;
            clf(obj.h_fig_plot)
            
            t = obj.h_table.Data;
            enabled_mask = t.enabled';
            enabled_channel_indices = find(enabled_mask);

            n_channels2 = length(enabled_channel_indices);

            colors = colororder(obj.h_fig_plot);
            if n_channels2 > size(colors,1)
                colors = repmat(colors,n_channels2/ceil(size(colors,1)),1);
            end

            h_axes = cell(1,n_channels2);
            empty_plot_mask = false(1,n_channels2);
            for i = 1:n_channels2
                h_axes{i} = subplot(n_channels2,1,i,'Parent',obj.h_fig_plot);
                hold(h_axes{i},'on')

                cur_channel_index = enabled_channel_indices(i);
                obj.h_status_label.Text = sprintf('Plotting: %d',cur_channel_index);

                if ~isempty(which('plotBig'))
                    [data,time] = obj.h_file.getChannelData(cur_channel_index,...
                        record_id,'datetime_out',true,'return_object',false,...
                        'time_as_object',true);
                    if isempty(data)
                        %do nothing
                        empty_plot_mask(i) = true;
                    else
                        plotBig(h_axes{i},time,data,'Color',colors(i,:))
                    end
                else
                    [data,time] = obj.h_file.getChannelData(cur_channel_index,...
                        record_id,'datetime_out',true,'return_object',false);
                    plot(time,data,'Color',colors(i,:));
                end
                %TODO: Add on units
                %
                %
                ylabel(h_axes{i},obj.h_file.channel_names{cur_channel_index})
            end
            
        
            %Linking axes
            %-------------------------------------------------------
            %   This turns out to be tough if data are missing
            h_axes = [h_axes{:}];
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
            pct = pct./sum(pct)*(0.94 - n_channels2*0.01);
            b = 0.03;
            for i = length(h_axes):-1:1
                h_axes(i).Position(2) = b;
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
                    t.y_min(cur_row) = ylim(1);
                    y.y_max(cur_row) = ylim(2);
                else
                    %else, set ylim
                    ylim(1) = t.y_min(cur_row);
                    ylim(2) = t.y_max(cur_row);
                    h_axes(i).YLim = ylim;
                end
            end

            %Comment drawing
            %----------------------------------------------------------
            comments = obj.h_file.getAllComments('output','table','use_datetime',true);
            comments = comments(comments.record == record_id,:);
            if ~isempty(comments)
                for i = 1:n_channels2
                    %text
                    %id
                    %absolute_time
                    keyboard
                end
            end

            obj.h_status_label.Text = '';

        end
    end
end