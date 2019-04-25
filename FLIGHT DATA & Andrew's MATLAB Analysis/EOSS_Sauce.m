% Script by Andrew Brodsky

% This script is intended to align EOSS's 1-second flight data with the
% user's flight data by merging the nearest-timestamped data point in the
% EOSS file with every data point in the flight file. (This script assumes
% that the timing of EOSS' electronics is less prone to drift than our
% Arduinos).

% NOTE: Both the EOSS file and the flight file must have the same units of
% time for this to work! In addition, the 'zero' of time in BOTH files must
% be the launch time.

% Notes for posterity: In our data, flight is seen to begin at 7.752
% minutes (based on accelerometer data). In HANDSSFLIGHT, this is row 4408;
% in GEIGERFLIGHT, this is just after row 31.

clc;

startPoint=1; 
% the starting search index in the EOSS file; increases with time as we're
% only looking for higher and higher numbers.

runAvgEOSSAltVsCounts=zeros(length(runAvgCountsVsMins),2); % preallocate a variable

for searchIndex=1:length(runAvgCountsVsMins)
    
    for searchBound=startPoint:height(EOSSFlightData)
        candidateTime=EOSSFlightData.MissionMins(searchBound);
        
        % did we find a point with a slightly greater time than our target?
        if candidateTime>=runAvgCountsVsMins(searchIndex,1) 
            
            upperIndex=searchBound;
            lowerIndex=searchBound-1;
            startPoint=searchBound;
            
            break;
        end
        
    end
    
    
        if abs(EOSSFlightData.MissionMins(upperIndex)-runAvgCountsVsMins(searchIndex,1))...
                <=abs(EOSSFlightData.MissionMins(lowerIndex)-runAvgCountsVsMins(searchIndex,1))
            runAvgEOSSAltVsCounts(searchIndex,1)=(EOSSFlightData.GPS_altitude(upperIndex)); % GPS altitude
            runAvgEOSSAltVsCounts(searchIndex,2)=(runAvgCountsVsMins(searchIndex,2)); % muon count
        else
            runAvgEOSSAltVsCounts(searchIndex,1)=(EOSSFlightData.GPS_altitude(lowerIndex)); % GPS altitude
            runAvgEOSSAltVsCounts(searchIndex,2)=(runAvgCountsVsMins(searchIndex,2)); % muon count
        end
        
end

clear searchIndex lowerIndex upperIndex searchBound startPoint candidateTime
            
            
            
            

