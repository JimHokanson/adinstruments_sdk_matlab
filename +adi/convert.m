function save_path = convert(file_path_or_paths,varargin)
%
%   adi.convert(*file_path,varargin)
%
%   This function will save a .adicht file's contents into a .mat file 
%   (v7.3) or a hdf5 file
%
%   The format is a bit awkward since it was originally written using a
%   32bit SDK which meant that partial reads and writes needed to be
%   supported.
%
%   Once converted, the converted file can be read by this program as well.
%
%   Optional Inputs:
%   ----------------
%   file_path_or_paths : str or cellstr (default: prompts user)
%       Path to the file or files. If omitted a prompt will ask the user 
%       to select the file to convert.
%   format : {'h5','mat'} (default 'mat')
%       The format to convert the file to. H5 (HDF5) requires additional
%       code, located at:
%           https://github.com/JimHokanson/hdf5_matlab
%   conversion_options: {adi.h5_conversion_options OR adi.mat_conversion_options}
%       These classes provide access to the conversion options. The main 
%       point of these options (at least initially) was to have control
%       over options that impact how fast the data is written (and then
%       subsequently written)
%   save_path : 
%       Final file save path. This is not recommended for multiple files to
%       convert
%   save_root : 
%       Folder to save converted files in. See also "root_path"
%   root_path :
%       If this is specified in addition to save_root then files are saved
%       in deeper directories after swapping this value for save_root. In
%       other words a file at data/type_1/ coulde be moved to
%       new_data/type_1 either via save_root = 'new_data/type_1' or more
%       generically for other files in 'data' via:
%           save_root = 'new_data'
%           root_path = 'data'
%
%   Examples:
%   ---------
%
%
%
%   See Also:
%   adi.h5_conversion_options
%   adi.h5_mat_conversion_options

persistent base_path

in.conversion_options = []; %{adi.mat_conversion_options, adi.h5_conversion_options}
in.format = 'mat'; %or 'h5'
in.save_path = '';
in.save_root = '';
in.root_path = ''; %To match for save root
in.no_exist_only = false;
in.verbose = false;
in = adi.sl.in.processVarargin(in,varargin);

if in.format(1) == '.'
    in.format(1) = [];
end
   
if nargin == 0 || isempty(file_path_or_paths)
    
    file_path_or_paths = adi.uiGetChartFile('prompt','Pick a file to convert','start_path',base_path,'multi_select',true);
    
    if isnumeric(file_path_or_paths)
        return
    end
    
else
    if ischar(file_path_or_paths) && exist(file_path_or_paths,'dir') == 7
       %Get list of adicht files ... 
       folder_path = file_path_or_paths;
       files = dir(fullfile(folder_path,'*.adicht'));
       file_path_or_paths = adi.sl.dir.fullfile(folder_path,{files.name});
    end
end

if ischar(file_path_or_paths)
    file_path_or_paths = {file_path_or_paths};
end
%This may need to change with files from different directories ...
base_path = fileparts(file_path_or_paths{1});

for iFile = 1:length(file_path_or_paths)

    cur_file_path = file_path_or_paths{iFile};
    
    %This may be empty, which yields control of the save path
    %to the convertor
    save_path = h__getSavePath(in,cur_file_path);
    
    if in.verbose
        %TODO: Print out what is being converted
        [~,file_name] = fileparts(cur_file_path);
        fprintf('Converting: %s\n',file_name);
    end
 
    file_obj = adi.readFile(cur_file_path);    
    
    switch in.format
        case 'h5'
            %adi.file.exportToMatFile
            save_path = file_obj.exportToHDF5File(save_path,in.conversion_options);
        case 'mat'
            %adi.file.exportToMatFile
            if ~isempty(in.conversion_options)
                in.conversion_options.verify()
            end
            save_path = file_obj.exportToMatFile(save_path,in.conversion_options);
        otherwise
            error('Unrecognized format option: %s',in.format);
    end

end
end

function save_path = h__getSavePath(in,cur_file_path)
%
%Save to the save_root. Preserve structure if root path is specified.

[file_root_path,file_name] = fileparts(cur_file_path);

if isempty(in.save_root)
    %If empty the converter will save it next to the original file
    save_path = in.save_path;
else
    if isempty(in.root_path)
        save_path = fullfile(in.save_root,file_name); 
    else
        if strncmp(in.root_path,file_root_path,length(in.root_path))
            start_I = length(in.root_path)+1;
            extra_path = file_root_path(start_I:end);
            save_path = fullfile(in.save_root,extra_path,file_name);
        else
            error('root path needs to be in the file path being converted')
        end
    end
end
end