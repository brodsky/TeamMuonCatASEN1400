% This script correlates the pressure from the countsVsPress file with the
% corresponding altitude data from the standardATMValues file.

countsVsAltitude=zeros(length(countsVsPress),2);

for pressIndex=1:length(countsVsPress)
    
    for searchBound=1:length(standardATMValues)
        pressToCheck=standardATMValues(searchBound,4);
        
        if pressToCheck<=countsVsPress(pressIndex,1) % the time to find a match for
            
            upperIndex=searchBound;
            lowerIndex=searchBound+1;
            
            break;
        end
        
    end
    
    
        if abs(standardATMValues(upperIndex,4)-countsVsPress(pressIndex,1))...
                <=abs(standardATMValues(lowerIndex,4)-countsVsPress(pressIndex,1))
            countsVsAltitude(pressIndex,1)=standardATMValues(upperIndex,6); % pressure (altitude)
            countsVsAltitude(pressIndex,2)=countsVsPress(pressIndex,2); % muon CPM
        else
            countsVsAltitude(pressIndex,1)=standardATMValues(lowerIndex,6); % pressure (altitude)
            countsVsAltitude(pressIndex,2)=countsVsPress(pressIndex,2); % muon CPM
        end
        
end

clear pressIndex lowerIndex upperIndex searchBound startPoint pressToCheck
            
            
            
            