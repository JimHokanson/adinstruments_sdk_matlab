classdef adi
    %
    %   Class:
    %   adi
    
    properties
    end
    
    methods (Hidden,Static)
        function createBlankFileAtPath(file_path)
            %
            %   adi.createBlankFileAtPath(file_path)
           repo_path = adi.sl.stack.getPackageRoot();
           blank_file_path = fullfile(repo_path,'files','blank_labchart_8_file.adicht');
           copyfile(blank_file_path,file_path)
        end
        function [file_path, file_root] = uiGetChartFile(varargin)
            %
            %
            %   This function can be used to select a particular LabChart
            %   file.
            %
            %   Output:
            %   -------
            %   file_path : str, 0, or cellstr
            %       If the user cancels the output is 0. Otherwise this is
            %       the full path to the file.
            
            in.multi_select = false;
            in.prompt = 'Pick a file to read';
            in.start_path = '';
            in = adi.sl.in.processVarargin(in,varargin);
            
            filter_specifications = ...
                {'*.adicht','Labchart Files (*.adicht)'; ...
                '*.h5','HDF5 Files (*.h5)';...
                '*.mat','Matlab Files (*.mat)'};
            
            if in.multi_select
                multi_select_value = 'on';
            else
                multi_select_value = 'off';
            end
            
            if isempty(in.start_path)
                [file_name_or_names,file_root] = uigetfile(filter_specifications,in.prompt,'MultiSelect',multi_select_value);
            else
                [file_name_or_names,file_root] = uigetfile(filter_specifications,in.prompt,in.start_path,'MultiSelect',multi_select_value);
            end
            
            if isnumeric(file_name_or_names)
                file_path = 0;
            else
                if ischar(file_name_or_names)
                    file_path = fullfile(file_root,file_name_or_names);
                    if in.multi_select
                        file_path = {file_path};
                    end
                else
                    n_files = length(file_name_or_names);
                    file_path = cell(1,n_files);
                    for iFile = 1:n_files
                       file_path{iFile} = fullfile(file_root,file_name_or_names{iFile}); 
                    end
                end
            end
        end
    end
    
end

