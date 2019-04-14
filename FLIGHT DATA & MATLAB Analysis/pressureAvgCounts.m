countSum=0;
altitudeSum=0;

bins=100; % the important bit
sample=floor(length(countsVsAltitude)/bins);

avgPressureCounts=zeros(bins,2);

for binNumber=1:bins-1
    
    for binSample=1:sample
        altitudeSum = altitudeSum + countsVsAltitude(sample*(binNumber-1)+binSample,1);
        countSum = countSum + countsVsAltitude(sample*(binNumber-1)+binSample,2);
    end
    
    avgPressureCounts(binNumber,1)=altitudeSum/sample;
    avgPressureCounts(binNumber,2)=countSum/sample;
    
    countSum=0;
    altitudeSum=0;
    
end

leftoverLength=length(countsVsAltitude)-sample*(bins-1);

for lastIndices = (sample*(bins-1)+1):length(countsVsAltitude)
    
    altitudeSum = altitudeSum + countsVsAltitude(lastIndices,1);
    countSum = countSum + countsVsAltitude(lastIndices,2);
    
    avgPressureCounts(bins,1)=altitudeSum/leftoverLength;
    avgPressureCounts(bins,2)=countSum/leftoverLength;
    
end

scatter(avgPressureCounts(:,1),avgPressureCounts(:,2))
clear altitudeSum bins binNumber binSample countSum lastIndices leftoverLength sample
        
        
        
        
        