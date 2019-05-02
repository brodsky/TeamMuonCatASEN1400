% Script by Andrew Brodsky

% This script is intended to align EOSS's 1-second flight data with the
% user's flight data by merging the nearest-timestamped data point in the
% EOSS file with every data point in the flight file. (This script assumes
% that the timing of EOSS' electronics is less prone to drift than our
% Arduinos).

% NOTE: Both the EOSS file and the flight file must have the same units of
% time for this to work! In addition, the 'zero' of time in BOTH files must
% be the launch time.

% Notes for posterity: EOSS' data show that launch occurred at 12:29:33
% UTC. In our data, flight is seen to begin at 7.752 minutes into the file
% (based on accelerometer data). In HANDSSFLIGHT, this is row 4408; in
% GEIGERFLIGHT, this is just after row 31. 

% EOSS' data show that landing occurred at 14:53:42 UTC. Our satellite
% appears to hit the ground at 144.3526 minutes after launch. In
% HANDSSFLIGHT, this occurs at T+144.3526 (row 86489); in GEIGERFLIGHT,
% this is just after row 608.

% By EOSS's data, flight lasted 144.15 minutes, compared to our 144.35
% minutes.

clc;

searchStartPoint=1;
% the starting search index in the EOSS file; increases with time as we're
% only looking for higher and higher numbers.

columnNumber=7;
OldEOSSAltVsAccZ=zeros(height(TeamScrewUpHSSData),2); % preallocate a variable

for searchIndex=1:height(TeamScrewUpHSSData)
    
    for searchBound=searchStartPoint:height(Fall2017EOSSData)
        candidateTime=Fall2017EOSSData.MissionMins(searchBound);
        
        % did we find a point with a slightly greater time than our target?
        if candidateTime>=TeamScrewUpHSSData{searchIndex,1} 
            
            upperIndex=searchBound;
            lowerIndex=searchBound-1;
            searchStartPoint=searchBound-1;
            
            break;
        end
        
    end
    
    
        if abs(Fall2017EOSSData.MissionMins(upperIndex)-TeamScrewUpHSSData{searchIndex,1})...
                <=abs(Fall2017EOSSData.MissionMins(lowerIndex)-TeamScrewUpHSSData{searchIndex,1})
            OldEOSSAltVsAccZ(searchIndex,1)=(Fall2017EOSSData.GPSaltitude(upperIndex)); % GPS altitude
            OldEOSSAltVsAccZ(searchIndex,2)=(TeamScrewUpHSSData{searchIndex,columnNumber}); % data
        else
            OldEOSSAltVsAccZ(searchIndex,1)=(Fall2017EOSSData.GPSaltitude(lowerIndex)); % GPS altitude
            OldEOSSAltVsAccZ(searchIndex,2)=(TeamScrewUpHSSData{searchIndex,columnNumber}); % data
        end
        
end

clear searchIndex lowerIndex upperIndex searchBound searchStartPoint candidateTime columnNumber
            
            
            
            

