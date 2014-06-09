function conversion_speed_testing

file_path = 'C:\D\GSK_Data\140204 control cmg.adicht';
file_path = 'C:\D\GSK_Data\140207 control cmg.adicht';
mat_fpath = 'C:\D\GSK_Data\140204 control cmg.mat';

if false
tic;
adinstruments.convert(file_path,'format','mat');
toc;
end

%Summary:
%File Size : 105 MB
%Total Time: 28 seconds
%163 reads of 21 channels (105 MB total) - 7.4 s
%Remaining time is mostly writing


if false
tic;
h = load(mat_fpath,'data__chan_3_rec_4');
toc;
end
%# Values: 91,434,500 - 730 MB in memory - on disk maybe 50 MB
%Channel read time: 2.637 seconds

tic;
adinstruments.convert(file_path,'format','h5');
toc;