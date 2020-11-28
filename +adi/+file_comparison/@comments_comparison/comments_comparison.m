classdef comments_comparison < handle
    %
    %   Class:
    %   adi.file_comparison.comments_comparison
    
    properties
        n_comments1
        n_comments2
        %Comments in 1 only
        %Comments in 2 only
        
        
        %----------------------------------------------------
        %ID:
        %
        %   in1, in2, string_match?, str1, str2, time_match, t1, t2
        
    end
    
    methods
        function obj = comments_comparison(all_c1,all_c2)
            
            
            s_all = cell(1,length(all_c1)+length(all_c2));
            ids2 = [all_c2.id];
            for i = 1:length(all_c1)
                c1 = all_c1(i);
                cur_id = c1.id;
                
                s = struct('in1',true,'in2',true,'string_match',false,...
                    'str1',c1.str,'str2','',...
                    'time_match',false,'r1',c1.record,'t1',c1.time,'r2',NaN,'t2',NaN);

                
                I = find(cur_id == ids2,1);
                if ~isempty(I)
                else
                end
                
            end
        end
    end
end