function unix_time = matlabToUnix(matlab_time,utc_offset)
%x Convert Matlab time to Unix Time
%
%   unix_time = sl.datetime.matlabToUnix(matlab_time,*utc_offset)
%
%   TODO: Finish documentation
%
%   See Also:
%   sl.datetime.getTimeZone
%   sl.datetime.unixToMatlab

utc_offset = 0;

% if ~exist('utc_offset','var') || isempty(utc_offset)
%     utc_offset = sl.datetime.getTimeZone;
% end

SECONDS_IN_DAY = 86400;
UNIX_EPOCH     = 719529;

unix_time = (matlab_time - utc_offset/24 - UNIX_EPOCH).*SECONDS_IN_DAY;

end

%Testing:
%datestr(sl.datetime.unixToMatlab(sl.datetime.matlabToUnix(now)))