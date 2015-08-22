function mergeComments(varargin)
%
%   adi.postp.mergeComments()
%
%   Examples:
%   ---------
%   adi.postp.mergeComments('final_file_path','C:\Users\RNEL\Desktop\merge_adi_test\150310_J_01_Wistart_PGE2.adicht')

in.final_file_path = '';
in = sl.in.processVarargin(in,varargin);


final_file_path = adi.uiGetChartFile('prompt','select file to add comments to');

%commented_files

commented_files_paths = adi.uiGetChartFile('multi_select',true,'prompt',...
    'Select files that contain new comments to move');

final_file = adi.readFile(final_file_path);

keyboard

end