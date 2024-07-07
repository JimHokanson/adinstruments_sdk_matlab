function mergePDFs(input_file_paths,output_file_path,varargin)
%
%   sl.io.mergePDFs(input_file_paths,output_file_path)
%
%   Based on:
%   https://www.mathworks.com/matlabcentral/fileexchange/89127-merge-pdf-documents


in.delete_inputs = false;
in = adi.sl.in.processVarargin(in,varargin);

%https://pdfbox.apache.org/docs/2.0.5/javadocs/org/apache/pdfbox/io/MemoryUsageSetting.html#setupMainMemoryOnly()
memory_settings = org.apache.pdfbox.io.MemoryUsageSetting.setupMainMemoryOnly();

%https://pdfbox.apache.org/docs/2.0.1/javadocs/org/apache/pdfbox/multipdf/PDFMergerUtility.html
merger = org.apache.pdfbox.multipdf.PDFMergerUtility;

for i = 1:length(input_file_paths)
    if ~exist(input_file_paths{i},'file')
        error('File does not exist: %s',input_file_paths{i})
    end
    merger.addSource(input_file_paths{i});
end

merger.setDestinationFileName(output_file_path)

merger.mergeDocuments(memory_settings)

if in.delete_inputs
    for i = 1:length(input_file_paths)
        delete(input_file_paths{i});
    end
end

end