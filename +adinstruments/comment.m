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
       %TODO: Add record id
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
%            %TODO: This should cause a nice display of all comments
%         end
    end
    
end

