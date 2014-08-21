classdef adi
    %
    %   Class:
    %   adi
    
    properties
    end
    
    methods (Hidden,Static)
        function [file_path, file_root] = uiGetChartFile(varargin)
            %
            %
            %   This function can be used to select a particular LabChart
            %   file.
            %
            %   Output:
            %   -------
            %   file_path : str or 0
            %       If the user cancels the output is 0. Otherwise this is
            %       the full path to the file.
            
            in.prompt = 'Pick a file to read';
            in.start_path = '';
            in = adi.sl.in.processVarargin(in,varargin);
          
            filter_specifications = ...
                {'*.adicht','Labchart Files (*.adicht)'; ...
                '*.h5','HDF5 Files (*.h5)';...
                '*.mat','Matlab Files (*.mat)'};
            
            if isempty(in.start_path)
                [file_name,file_root] = uigetfile(filter_specifications,in.prompt);
            else
                [file_name,file_root] = uigetfile(filter_specifications,in.prompt,in.start_path);
            end
            
            if isnumeric(file_name)
                file_path = 0;
            else
                file_path = fullfile(file_root,file_name);
            end
        end
    end
    
end

