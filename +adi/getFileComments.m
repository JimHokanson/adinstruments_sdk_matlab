function t = getFileComments(file_path)
%X Returns all comments from the file
%
%   t = adi.getFileComments(*file_path)
%
%   Inputs
%   ------
%   file_path : optional
%       If not specified the user is prompted
%
%   Outputs
%   -------
%   t : table
%       A table with all of the comments in it
%
%   Examples
%   --------
%   t = adi.getFileComments

persistent root_folder;

% Check if filePath is not provided or empty.
if nargin < 1 || isempty(file_path)
    if isempty(root_folder) || ~exist(root_folder,'dir')
        % If the rootFolder is not set, ask the user for the file path.
        [file_name, file_folder] = uigetfile('*.adicht*', 'Select a file to read');
        if file_name == 0
            t = [];
            return
        end
        file_path = fullfile(file_folder, file_name);
        root_folder = file_folder;
    else
        % If the rootFolder is set, start from the previous root folder.
        [file_name, file_folder] = uigetfile('*.adicht*', 'Select a file to read',root_folder);
        if file_name == 0
            t = [];
            return
        end
        file_path = fullfile(file_folder, file_name);
        root_folder = file_folder;
    end
else
    % If filePath is provided, update the root folder to the file's directory.
    [file_folder, ~, ~] = fileparts(file_path);
    root_folder = file_folder;
end

f = adi.readFile(file_path);

t = f.getAllComments('output','table');

end
