function paths_out = fullfile(root,paths_in)
%fullfile  Appends paths to a root path
%
%   paths_out = sl.dir.fullfile(root,paths_in)
%
%   Performs the equivalent of fullfile() on each root/pathsIn pair. It
%   tries to accomplish this in the quickest way possible.
%
%   Inputs:
%   -------
%   root : (string), root path for appending to
%   paths_in : (cellstr), paths to append to the root
%
%   Outputs:
%   --------
%   paths_out : (cellstr) resultant concatenation of paths
%
%   Examples:
%   ---------
%   1) 
%   root = 'C:\'
%   paths_in = {'test' 'cheese'};
%   paths_out = sl.dir.fullfile(root,paths_in)
%   paths_out =>
%       {'C:\test' 'C:\cheese'}
%
%   IMPROVEMENTS
%   ------------
%   1) I don't like the name of this file. I might rename it ...
%       => fullfile would be fine
%
%   See Also:
%   fullfile

if isempty(paths_in)
    paths_out = {};
    return
elseif ischar(paths_in)
    error('paths_in must be a cell array of strings')
end

fs = filesep;
if root(end) ~= fs
    root = [root fs];
end

n_paths = length(paths_in);
paths_out = cell(1,n_paths);
for iPath = 1:n_paths
    paths_out{iPath} = [root paths_in{iPath}];
end

%CODE ALTERNATIVES
%--------------------------------------------------------------------------

%The above approach takes only about 60% of the time this one takes ...
%     paths_out = cellfun(@makePath_fsPresent,paths_in,'un',0);
%
%     function myPath = makePath_fsPresent(inputPath)
%         myPath = [root inputPath];
%     end

end