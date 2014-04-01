%Docuementation for automation found at:
%http://forum.adinstruments.com/viewtopic.php?f=7&t=296&p=542&hilit=64bit#p542

lib_path = 'C:\Users\Jim\Documents\ADInstruments\SimpleDataFileSDK\bin\ADIDatIOWin.dll';
hdr_path = 'C:\Users\Jim\Documents\ADInstruments\SimpleDataFileSDK\adidat\include\ADIDatCAPI.h';

loadlibrary(lib_path,hdr_path)

file_path = 'Z:\Jim_temp\140204\140204 control cmg.adicht'


%http://www.mathworks.com/help/matlab/matlab_external/handling-com-data-in-matlab-software.html
%http://www.mathworks.com/help/matlab/using-com-objects-in-matlab.html

%http://stackoverflow.com/questions/4055793/how-to-get-an-activex-components-registered-path
%http://www.mathworks.com/help/matlab/ref/winqueryreg.html
%http://msdn.microsoft.com/en-us/library/windows/desktop/ms221027%28v=vs.85%29.aspx
clsid = winqueryreg('HKEY_CLASSES_ROOT','COM.ADIChart\clsid')

ls32 = winqueryreg('HKEY_CLASSES_ROOT','CLSID',clsid,'LocalServer32')

%ITypeLib
%ITypeInfo
%ITypeComp


%VIEW IN EXCEL
% - ALT-F11




app = actxserver('ADIChart.Application')

doc = actxserver('ADIChart.Document')

app = doc.Application;

app.CloseActiveDocument(true)

%Yikes, this might show a popup in the application ...
app.Open(file_path)

doc = app.ActiveDocument;

wtf = actxserver('ADIDataLib.

%What information can we get?
%-------------------------------------
%GetRecordLength(block_num) -  returns the length in ticks (the sample time 
%   of the fastest channel) of the block indicated by the block index (starting from 0)
%
%NumberOfChannels
%GetChannelName(channel_number)
%NumberOfRecords
n_channels = doc.NumberOfChannels;
channel_names = cell(1,n_channels);
for iChan = 1:n_channels
   channel_names{iChan} = doc.GetChannelName(iChan); 
end

n_blocks = doc.NumberOfRecords;
n_samples_per_block = zeros(1,n_blocks);
for iBlock = 1:n_blocks
   n_samples_per_block(iBlock) = doc.GetRecordLength(iBlock-1);
end

%GetChannelData
%------------------------------------
%GetChannelData(flags As ChannelDataFlags, channelNumber As Long, blockNumber As Long, startSample As Long, numSamples As Long)

channel_data_flag  = 1; %double
channel_number_get = 1; %pressure
block_number       = 4; %1 based or 0 based??? - seems 1 based :/
start_sample       = 1;


read_size = 1000000;

n_samples_read = n_samples_per_block(block_number);

n_reads = n_samples_read/read_size;

tic
cur_start = 0;
cur_end   = 0;
final_data = zeros(1,n_samples_read);
for iRead = 1:n_reads-1
   cur_start = cur_end + 1;
   cur_end   = cur_start + read_size - 1;
   final_data(cur_start:cur_end) = doc.GetChannelData(channel_data_flag,channel_number_get,block_number,cur_start,read_size);
end

n_remaining_samples = n_samples_read - cur_end;
if n_remaining_samples > 0
final_data(cur_end+1:end) = doc.GetChannelData(channel_data_flag,channel_number_get,block_number,cur_end+1,n_remaining_samples);
end
toc

%sampling_rate_per_block
%doc.GetRecordSecsPerTick(2)

%GetUnits(channel_number,block_number)

