% --- Убираются все линии с графика
function linesOff()
    realPlot = evalin('base','realPlot');
    realIndex = evalin('base','realIndex');
    voiPlot = evalin('base','voiPlot');
    voiIndex = evalin('base','voiIndex');
    hypoPlot = evalin('base','hypoPlot');
    hypoIndex = evalin('base','hypoIndex');
    
    setLinesOff(realPlot(realIndex));
    setLinesOff(voiPlot(voiIndex));
    setLinesOff(hypoPlot(hypoIndex));