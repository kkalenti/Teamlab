
function setLinesOff()
    realPlot = evalin('base','realPlot');
    realSize = size(realPlot);

    voiPlot = evalin('base','voiPlot');
    voiSize = size(voiPlot);
    
    hypoPlot = evalin('base','voiPlot');
    hypoSize = size(hypoPlot);
    
    for i = 1 : voiSize(2)
        setLinesOff(voiPlot(i))
    end
    
    for i = 1 : realSize(2)
        setLinesOff(realPlot(i))
    end
    
    for i = 1 : hypoSize(2)
        setLinesOff(hypoPlot(i))
    end