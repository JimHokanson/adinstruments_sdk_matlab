function file_writer = createFile(file_path)
%
%   file_writer = adi.createFile(file_path)

file_h = adi.sdk.createFile(file_path);

data_writer_h = adi.sdk.createDataWriter(file_h);

file_writer = adi.file_writer(file_path, file_h, data_writer_h);



end