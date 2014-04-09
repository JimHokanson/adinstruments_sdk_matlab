classdef comment < handle
    %
    %   Class: adinstruments.comment
    
    % //          tickPos                 - receives the tick position of the comment in the record [outparam]
    % //          commentNum              - receives the number of the comment [outparam]
    % //          channel                 - receives the channel of the comment (-1 for all channel comments) [outparam]
    
    properties
       str
       id
       tick_position
       channel %-1 for all channels
    end
    
    methods
        function obj = comment(comment_string,tick_pos,channel,comment_num)
            
           obj.str           = comment_string;
           obj.id            = comment_num;
           obj.tick_position = tick_pos;
           obj.channel       = channel;
        end
%         function objs = sortByID(objs)
%             
%         end
%         function pretty_print(objs)
%            
%         end
    end
    
end

