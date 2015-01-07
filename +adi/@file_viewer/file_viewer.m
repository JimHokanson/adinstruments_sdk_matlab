classdef file_viewer
    %
    %   Class:
    %   adi.file_viewer
    %
    
    properties
    end
    
    methods
        function obj = file_viewer(file_path)
            %
            %   obj = adi.file_viewer(file_path)
            %
            %   See Also:
            %   ---------
            %   adi.view
            
            %TODO:
            %---------------------------
            %- Display comments in panel
            %   - click on comment to go to comment
            %- Add title to figue window
            %- manual ylims - create nice interface for this
            %- support panning
            %- build in processing support - filtering
            %- add a channel
            %- reorder channels
            %- display comments on figures
            %- allow saving viewing settings into a file for 
            %   later retrieval
            
            f = adi.readFile(file_path);
            
            for iChannel = 1:f.n_channels
                cur_channel_name = f.channel_names{iChannel};
                chan_obj = f.getChannelByName(cur_channel_name);
                
                %TODO: Allow array retrieval of data for multiple records
                all_chan_data = cell(1,f.n_records);
                for iRecord = 1:f.n_records
                   all_chan_data{iRecord} = chan_obj.getData(iRecord);
                end
                
                subplot(f.n_channels,1,iChannel);
                plot([all_chan_data{:}])
                
            end
            
            set(gcf,'name',file_path);
            sl.plot.postp.linkFigureAxes(gcf,'x');
            
            keyboard
           
        end
    end
    
end

