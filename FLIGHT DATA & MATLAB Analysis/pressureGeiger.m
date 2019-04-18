% This script correlates the timestamp from the GEIGERFLIGHT file with the
% nearest pressure reading from the HANDSSFLIGHT file.

startPoint=1;
countsVsPress=zeros(height(GEIGERFLIGHT),2);

for geigerIndex=1:height(GEIGERFLIGHT)
    
    for searchBound=startPoint:height(HANDSSFLIGHT)
        timeToCheck=HANDSSFLIGHT{searchBound,1};
        
        if timeToCheck>=GEIGERFLIGHT{geigerIndex,1} % the time to find a match for
            
            upperIndex=searchBound;
            lowerIndex=searchBound-1;
            startPoint=searchBound;
            
            break;
        end
        
    end
    
    
        if abs(HANDSSFLIGHT{upperIndex,1}-GEIGERFLIGHT{geigerIndex,1})<=abs(HANDSSFLIGHT{lowerIndex,1}-GEIGERFLIGHT{geigerIndex,1})
            countsVsPress(geigerIndex,1)=(HANDSSFLIGHT{upperIndex,3}); % pressure (altitude)
            countsVsPress(geigerIndex,2)=(GEIGERFLIGHT{geigerIndex,8}); % muon count
        else
            countsVsPress(geigerIndex,1)=(HANDSSFLIGHT{lowerIndex,3}); % pressure (altitude)
            countsVsPress(geigerIndex,2)=(GEIGERFLIGHT{geigerIndex,8}); % muon count
        end
        
end

clear geigerIndex lowerIndex upperIndex searchBound startPoint timeToCheck
            
            
            
            