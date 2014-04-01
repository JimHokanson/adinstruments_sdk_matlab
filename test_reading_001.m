file_path = 'Z:\Jim_temp\140204\140204 control cmg.adicht';
data = sl.io.fileRead(file_path,'*uint8');

%http://forum.adinstruments.com/viewtopic.php?f=7&t=395
%First bytes in file:
%--------------------------------------
%A D I n s t r u m e n t s   C o m p o u n d   F i l e  - 2 bytes per
%character?
%
%FIRST BYTE:
%byte 129 - value = 27 - size
%
%File transversal
%----------------------------------------

%1 2 3 4

[start_text_I,end_text_I,strings_with_spaces] = regexp(char(data),'([\x20-\x7E]\x00){4,}','start','end','match');

strings = cellfun(@(x) x(1:2:end),strings_with_spaces,'un',0);


%COMMENTS
%--------------------------------------------------------------------------
%

N_BEFORE = 100;
N_AFTER  = 40;
u = unique(str_I);
n_strings = length(start_text_I);
before_string = zeros(n_strings,N_BEFORE,'uint8');
after_string  = zeros(n_strings,N_AFTER,'uint8');

for iStr = 2:n_strings
   cur_start_I = start_text_I(iStr);
   cur_end_I   = end_text_I(iStr);
   before_string(iStr,:) = data(cur_start_I-N_BEFORE:cur_start_I-1);
   after_string(iStr,:) = data(cur_end_I+1:cur_end_I+N_AFTER);
end

%FORMAT:
%--------------------------------
%Common Proceeding Binary:
%11 0 0 0 - indictes the size
%What is 1 0 0 128 ??????
%
%0   28    0    1    4    0    1    0    0  128   11    0    0    0  245  255  255  255
%
%A D I Root Storage:
%255  255    0    0    0    0  233   25    0    0    0    0    0    0    0    0    0    0
%=> 233 25 0 0 => 6633

cur_size_index = 0;
sizes = zeros(1,100000);
cur_data_index = 129;
done = false;
while ~done
   sz = uint32(data(cur_data_index:cur_data_index+3));
   cur_size_index = cur_size_index + 1;
   sizes(cur_size_index) = sz;
   cur_data_index = cur_data_index + sz - 1;
    
end