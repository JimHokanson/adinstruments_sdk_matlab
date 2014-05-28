classdef comment < sl.obj.display_class
    %
    %   Class:
    %   adinstruments.comment
    %
    %   Holds a comment.
    %
    %   NOTE: Comments can be moved after they are placed. I think
    %   this means that the comments might not be ordered by ID.
    %   Also comments can be deleted, which might cause gaps in the ID
    %   numbering as well.
    
    properties
        str  %The string content of the comment
        id   %The number associated with the comment, starts at ????
        tick_position %?????????
        %TODO: Add time since start of record and experiment ...
        channel %-1 indicates all channels
        record
        tick_dt
    end
    
    properties (Dependent)
        time
    end
    
    methods
        function value = get.time(obj)
            value = obj.tick_position*obj.tick_dt;
        end
    end
    
    methods
        function obj = comment(comment_string,tick_pos,channel,comment_num,record_id,tick_dt)
            
            obj.str           = comment_string;
            obj.id            = comment_num;
            obj.tick_position = tick_pos;
            obj.channel       = channel;
            obj.record        = record_id;
            obj.tick_dt       = tick_dt;
        end
        %         function objs = sortByID(objs)
        %
        %         end
        function pretty_print(objs)
            %
            %
            %   Example:
            %
            % Format
            % ID : time : str
            % Record #04
            % 002: 315.85: start pump
            % 003: 318.85: 5 ml/hr
            % 004: 1624.55: stop pump
            % 008: 1952.00: qp 1
            % 005: 2088.35: start pump
            % 006: 2782.95: stop pump
            % 007: 3011.50: qp 2
            
            all_records = [objs.record];
            [u,uI] = sl.array.uniqueWithGroupIndices(all_records);
            
            n_records = length(u);
            
            fprintf('Format\n');
            fprintf('ID : time : str\n');
            
            for iRecord = 1:n_records
                cur_record_indices = uI{iRecord};
                cur_record         = u(iRecord);
                n_indices          = length(cur_record_indices);
                
                fprintf('Record #%02d\n',cur_record);
                for iComment = 1:n_indices
                    cur_obj = objs(cur_record_indices(iComment));
                    fprintf('%03d: %0.2f: %s\n',cur_obj.id,cur_obj.time,cur_obj.str);
                end
            end
        end
        function [objs_out,times] = getCommentsForChannel(objs,channel_obj,record_id,x_limits)
            %
            %
            %   adinstruments.comment.getCommentsForChannel
            %
            %   Returns comments that:
            %   1) Have the same record as that being requested
            %   2) Pertain to the given channel
            %
            %   Inputs:
            %   -------
            %   channel_obj :
            %
            %   record_id   :
            %
            %   x_limits    :
            
            keep_mask = [objs.record] == record_id;
            kept_objs = objs(keep_mask);
            if isempty(kept_objs)
                objs_out = kept_objs;
                times    = [];
                return
            end
            
            %Channel filtering
            %-------------------------------
            temp_channels = [kept_objs.channel];
            
            keep_mask = temp_channels == -1 | temp_channels == channel_obj.id;
            kept_objs     = kept_objs(keep_mask);
            if isempty(kept_objs)
                objs_out = kept_objs;
                times    = [];
                return
            end
            
            %Time filtering
            %-------------------------------
            %TODO: Might need to subtract 1 ...
            obj_times_scaled = [kept_objs.tick_position]*channel_obj.tick_dt(record_id);
            
            keep_mask = obj_times_scaled >= x_limits(1) & obj_times_scaled <= x_limits(2);
            objs_out  = kept_objs(keep_mask);
            times     = obj_times_scaled(keep_mask);
        end
        function exportToMatFile(objs,m)
            
           m.comment_version = 1;
           
           m.comments = struct(...
                'str',              {objs.str},... 
                'id',               {objs.id},...
                'tick_position',    {objs.tick_position},...
                'channel',          {objs.channel},...
                'record',           {objs.record},...
                'tick_dt',          {objs.tick_dt});

        end
    end
    
end

