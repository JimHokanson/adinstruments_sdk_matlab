function labchart_crash_testing
%
%
%   The test consists of opening and closing a file many times. This seems
%   to cause 

FILE_OPTION = 2;

FILE_ROOT = 'F:\GSK\Rat_Expts\2014\edited\';

%file_name = '140710_J_02_SHR_PudStim.adicht'; %no comments
%file_name = '140715_J_01_SHR_PudStim.adicht';  %no comments
%file_name = '140609_J_01_SHR_EUS.adicht'; %10000 tries, no problem
%file_name = '140530_J_01_SHR_control.adicht'; %10000 tries, no problem

if FILE_OPTION == 1
file_name = '140724_J_01_SHR_PudStim.adicht'; %super large file
else
file_name = '140605_J_02_SHR_EUS_and_PudendalStim.adicht'; %crashed 1 time
%on # of records, but worked most others
end


file_path = fullfile(FILE_ROOT,file_name);

r = adi.readFile(file_path);
clear r

for iRun = 1:5000
r = adi.readFile(file_path);
clear r
end
disp('tested passed')