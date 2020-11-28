classdef file_comparison
    %
    %   Class:
    %   adi.file_comparison
    
    
    %{
    
        fc = adi.file_comparison(p1,p2);
    
    %}
    
    properties
        file_path1
        file_path2
        f1
        f2
        n_records1
        n_records2
    end
    
    methods
        function obj = file_comparison(path1,path2)
            %
            %   obj = adi.file_comparison(path1,path2)
            
            obj.file_path1 = path1;
            obj.file_path2 = path2;
            
            f1 = adi.readFile(path1);
            f2 = adi.readFile(path2);
            
            obj.n_records1 = f1.n_records;
            obj.n_records2 = f2.n_records;
            
            c1 = f1.getAllComments();
            c2 = f2.getAllComments();            
            adi.file_comparison.comments_comparison(c1,c2);
            
            keyboard
            
        end
    end
end

