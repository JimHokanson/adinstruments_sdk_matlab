test_reading_002.m

%Excel
%ALT-F11 to view visual basic
%Tools - Resources to load COM
%F2 to view com object

%ADInstruments.ADIData

wtf = actxserver('ADIData.IADIDataReader')

h=feval('COM.ADIDataLib_ADIDataObject', 'server', '', 'IDispatch');