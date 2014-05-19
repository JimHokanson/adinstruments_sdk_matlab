classdef channel_plotter < sl.obj.display_class
    %
    %   Class:
    %   adinstruments.channel_plotter
    
    properties
        time_format  = 'seconds' %
        % - seconds
        % - HH:MM:SS
        % - indices
        add_comments = true
        gain = 1
        
        %TODO: Add filters ...
        filters = {}
    end
    
    properties (Hidden)
        chan_obj
        line_handles
    end
    
    methods
        function obj = channel_plotter(chan_obj)
            obj.chan_obj     = chan_obj;
            obj.line_handles = cell(1,chan_obj.n_records);
        end
        function plotRecord(obj,record_id)
            %x Call this to plot data once everything is setup
            %   
            %
            
            %TODO: It would be nice to not actually create time
            %but to create instructions for time, since we are
            %sampling evenly ...
            [data,time] = obj.chan_obj.getAllData(record_id);
            
            %TODO: Fix this:
            %time = 1:length(time)
            
            if obj.gain ~= 1
                data = data/obj.gain;
            end
            
            %TODO: Filter data ...
            %------------------------------------------------
            
            
            lpr = sl.plot.big_data.LinePlotReducer(time,data);
            
            if obj.add_comments
                lpr.post_render_callback = @() renderComments(obj,lpr,record_id);
            end
            
            lpr.renderData;
            
            cur_units = obj.chan_obj.units{record_id};
            ylabel(cur_units)
            
            plot_handle = lpr.h_plot(1);
            s = struct;
            s.record_id  = record_id;
            s.start_time = 0;
            s.dt         = obj.chan_obj.dt(record_id);
            s.type       = 'data';
            set(plot_handle,'UserData',s)
            
            %http://www.mathworks.com/help/matlab/ref/datacursormode.html
            dcm_obj = datacursormode(gcf);            
            dcm_obj.UpdateFcn = @h__tickDisplay;
            
        end
        function renderComments(obj,lpr,record_id)
            
            %TODO: Add #s to comments
            N_POINTS_COMMENT_LINES = 100;
            comment_objs = obj.chan_obj.getRecordComments(record_id);
            if ~isempty(comment_objs)
                
                %Clear old lines
                %------------------------------------
                temp_line_handles = obj.line_handles{record_id};
                if ~isempty(temp_line_handles)
                   delete(temp_line_handles) 
                end
                
                %Get relevant comments ...
                %------------------------------------
                x_limits = lpr.x_limits;
                
                %adinstruments.comment.getCommentsForChannel
                [objs_out,times] = getCommentsForChannel(comment_objs,obj.chan_obj,record_id,x_limits);
                if isempty(objs_out)
                   return 
                end
                
                %Plot lines
                %-------------------------------------
                y_limits = lpr.y_limits;
                n_objs   = length(objs_out);
                temp_line_handles = zeros(1,n_objs);
                s = struct('type','comment','str',{objs_out.str});
                y_line = linspace(y_limits(1),y_limits(2),N_POINTS_COMMENT_LINES); %This allows us to put our data tip on the line at multiple locations
                for iObj = 1:n_objs
                   temp_line_handles(iObj) = line(times(iObj)*ones(1,N_POINTS_COMMENT_LINES),y_line,'Linestyle',':','Color','k','Parent',lpr.h_axes(1));
                   set(temp_line_handles(iObj),'UserData',s(iObj));
                end
            end
        end
    end
end

function output_txt = h__tickDisplay(~,ev_info)
%ev_info 
%   .Target  : handle
%   .Position: [x y]

s = get(ev_info.Target,'UserData');
if isempty(s) 
    %TODO: For lines, add comments ...
    %NOTE: s will no longer be empty ...
    output_txt = '';
elseif strcmp(s.type,'comment')
    output_txt = s.str;
else
    xy = ev_info.Position;
    cur_index  = (xy(1)-s.start_time)/s.dt + 1;
    output_txt = sprintf(' index: %d\n     y: %0.3f\n     x: %0.3f',uint64(cur_index),xy(1),xy(2));
end

end

