function file_writer = createFile(file_path,copy_blank)
%
%   file_writer = adi.createFile(file_path)

is_new = ~exist(file_path,'file');


if copy_blank
    if is_new
       adi.createBlankFileAtPath(file_path)
    end
    file_h = adi.sdk.openFile(file_path,'read_and_write',true);
else
   file_h = adi.sdk.createFile(file_path); 
end
%I tried toggling between these options
%


data_writer_h = adi.sdk.createDataWriter(file_h);

file_writer = adi.file_writer(file_path, file_h, data_writer_h, is_new);



end