function printFile(file_path, varargin)
%
%   adi.printFile(file_path,varargin)


%{
adi.printFile(file_path)
%}


in.width_per_slide = 20*60;
in.overlap_width = 2*60;
in.print_size = [8.5 11];
in = adi.sl.in.processVarargin(in,varargin);


f = adi.readFile(file_path);

%# of active channels
%duration of all records

%Options
%---------------------
%- Ordering
%- % to show
%- width per slide (seconds)
%- print size
%- overlap
%- which channels to plot
%- need plot height info


%Need to go from absolute time to
record_starts = NaT(1,f.n_records);
record_ends = NaT(1,f.n_records);
for i = 1:f.n_records
    temp = f.records(i).data_start;
    record_starts(i) = datetime(temp,'ConvertFrom','datenum');
    record_ends(i) = record_starts(i) + seconds(f.records(i).duration);
end

total_duration_s = record_ends(end)-record_starts(1);

step_size = seconds(in.width_per_slide - in.overlap_width);
starts = record_starts(1):step_size:record_ends(end);
stops = starts + seconds(in.width_per_slide);

n_records = f.n_records;
n_pages = length(starts);

n_channels = f.n_channels;

%Scaling
%---------------------------------------------
%
%
%   This is only needed if no scaling is presented


% chan_data = cell(1,n_records);
chan_min = NaN(n_channels,1);
chan_max = NaN(n_channels,1);
for i = 1:n_channels
    for j = 1:n_records
        temp = f.getChannelData(i,j,'return_object',false);
        if ~isempty(temp)
            chan_min(i) = min(chan_min(i),min(temp));
            chan_max(i) = max(chan_max(i),max(temp));
        end
    end
end

colors = colororder();
if n_channels > size(colors,1)
    colors = repmat(colors,n_channels/ceil(size(colors,1)),1);
end


for i = 1:n_pages
    records_include = find(record_starts >= starts(i) & record_starts <= stops(i));
    %TODO: We could optional collapse here if certain channels are missing
    %for all records
    h_axes = cell(1,n_channels);
    for c = 1:n_channels
        h_axes{c} = subplot(n_channels,1,c);
        hold on
        for j = 1:length(records_include)
            cur_record = records_include(j);
            r_t1 = record_starts(cur_record);
            r_t2 = record_ends(cur_record);
            overlap_start = max(starts(i), r_t1);
            overlap_stop = min(stops(i), r_t2);

            %TODO: Support faster plotting

            


                [data,time] = f.getChannelData(c,cur_record,...
                    'time_range',[overlap_start,overlap_stop],...
                    'datetime_out',true,'return_object',false);
    
            if ~isempty(which('plotBig'))
                %What was the MATLAB bug?????
                
            else
                plot(time,data,'Color',colors(c,:));
            end

            %We could make this optional ...
            if r_t1 >= overlap_start && ...
                    r_t1 <= overlap_stop
                y = [chan_min(c) chan_max(c)];
                plot([r_t1 r_t1],y,'k')
            end


            %TODO: Add all comments

            %                channel_number_1b_or_name, ...
            %    block_number_1b,varargin)
        end
        set(gca,'YLim',[chan_min(c) chan_max(c)],'XLim',[starts(i),stops(i)])
    end
    keyboard

    %Adjust everything and print
    %   - page size
    %   - tighten spacing
    %   - where to save
    %       - by default save to 
    %   - add title

end




end


function launchGUI()


end