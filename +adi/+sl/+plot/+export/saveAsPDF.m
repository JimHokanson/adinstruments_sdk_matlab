function saveAsPDF(h_fig,varargin)
%X Save figure as PDF with prompt for filename
%
%   adi.sl.plot.export.saveAsPDF(*h_fig,varargin)
%
%   Optional Inputs
%   ---------------
%   file_path 
%       Specify full path to file
%
%   Examples
%   --------
%   sl.plot.export.saveAsPDF(gcf,'file_path',file_path)
%
%   Improvements
%   ------------
%   1)DONE - update documentation Allow file specification as an input
%   2) Scale to print to a page size

in.file_path = '';
in = adi.sl.in.processVarargin(in,varargin);

if nargin == 0 || isempty(h_fig)
   h_fig = gcf; 
end

if isempty(in.file_path)
    [file_name,path_name] = uiputfile(...
        {'*.pdf','PDF file (*.pdf)'; ...
            '*.*',  'All Files (*.*)'}, ...
            'Save as', 'Untitled.pdf');

    if isequal(file_name,0) || isequal(path_name,0)
       %disp('User pressed cancel')
        return
    end
    file_path = fullfile(path_name, file_name);
else
    file_path = in.file_path;
end


%Ideally we wouldn't change anything ...
s1 = get(h_fig);
%The idea is to reset to s1 after changing

h_fig.Units = 'inches';
h_fig.PaperSize = h_fig.Position(3:4);
h_fig.PaperUnits = 'inches';
h_fig.PaperPosition = h_fig.Position;
h_fig.PaperPositionMode = 'auto';



print(h_fig,'-dpdf','-painters',file_path);
 
end