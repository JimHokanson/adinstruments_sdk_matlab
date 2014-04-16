classdef (Hidden) comment < handle
    %
    %   Class: adinstruments.comment
    %
    %   Holds a comment.
    %
    %   NOTE: The comments
    
    % //          tickPos                 - receives the tick position of the comment in the record [outparam]
    % //          commentNum              - receives the number of the comment [outparam]
    % //          channel                 - receives the channel of the comment (-1 for all channel comments) [outparam]
    
    properties
       str  %The string content of the comment
       id   %The number associated with the comment, starts at ????
       tick_position %?????????
       %TODO: Add time since start of record and experiment ...
       channel %-1 indicates all channels
       record
    end
    
    methods
        function obj = comment(comment_string,tick_pos,channel,comment_num,record)
            
           obj.str           = comment_string;
           obj.id            = comment_num;
           obj.tick_position = tick_pos;
           obj.channel       = channel;
           obj.record        = record;
        end
%         function objs = sortByID(objs)
%             
%         end
        function pretty_print(objs)
           %TODO: I think I want to filter by record first,
           %i.e. have record headers
           %
           %Record #1
           %-
           %-
           %Record #2
           %-
           %-
           %etc
           
           for iComment = 1:length(objs)
              cur_obj = objs(iComment); 
              fprintf('%03d: R-%03d: %s\n',cur_obj.id,cur_obj.record,cur_obj.str); 
           end
        end
    end
    
end

