% --- ��������� ��� ����� � �������
function linesOff()
    realPlot = evalin('base','realPlot');
    realIndex = evalin('base','realIndex');
    voiPlot = evalin('base','voiPlot');
    voiIndex = evalin('base','voiIndex');
    
    setLinesOff(realPlot(realIndex));
    setLinesOff(voiPlot(voiIndex));

% --- ������� ����� �������
function setLinesOff(inform)
    set(inform.ch1.coordinate,'Visible','off');
    set(inform.ch1.speed,'Visible','off');
    set(inform.ch1.acceleration,'Visible','off');
    
    set(inform.ch2.coordinate,'Visible','off');
    set(inform.ch2.speed,'Visible','off');
    set(inform.ch2.acceleration,'Visible','off');
    
    set(inform.ch3.coordinate,'Visible','off');
    set(inform.ch3.speed,'Visible','off');
    set(inform.ch3.acceleration,'Visible','off');
