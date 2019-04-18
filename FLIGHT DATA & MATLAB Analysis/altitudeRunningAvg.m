radiusOfAverage=15;
runAvgCountsVsAltitude=zeros((length(countsVsAltitude)-radiusOfAverage*2),2);

sampleSum=0;

for index=radiusOfAverage+1:length(countsVsAltitude)-(radiusOfAverage+1)
    
    for sample=index-radiusOfAverage:index+radiusOfAverage
        sampleSum=sampleSum+countsVsAltitude(sample,2);
    end
    
    runAvgCountsVsAltitude(index-radiusOfAverage,1)=countsVsAltitude(index-radiusOfAverage,1);
    runAvgCountsVsAltitude(index-radiusOfAverage,2)=sampleSum/(radiusOfAverage+1);
    
    sampleSum=0;
    
end

scatter(runAvgCountsVsAltitude(:,1),runAvgCountsVsAltitude(:,2))
title('Muon CPM vs Altitude (15-Point Running Average)');
xlabel('Altitude (m)');
ylabel('Muon Counts Per Minute (min)^-1');
legend('Combined Geiger Counter Data');
set(gca,'fontsize', 16, 'fontweight', 'bold');
clear index sample sampleSum radiusOfAverage
        
        
        
        
        