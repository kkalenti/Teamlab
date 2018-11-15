% --- Задаются первоначальные данные графика
function defaultSetting(handles)
set(handles.uibuttongroup1,'Visible','on');
set(handles.uibuttongroup7,'Visible','on');
set(handles.uipanel3,'Visible','on');
set(handles.pushbutton3,'Visible','on');

grid on;
hold on;
xlabel('Время, s');
ylabel('Координаты, m');

Real = evalin('base','Real');
VOI = evalin('base','VOI');

allRealCheckboxAssignin(Real);
voiCheckboxAssignin(VOI(1));

realPlot = evalin('base','realPlot');
realIndex = 1;
assignin('base','realIndex',realIndex);
voiPlot = evalin('base','voiPlot');

setListboxes(handles);

legend([realPlot(1).ch1.coordinate,realPlot(1).ch2.coordinate,realPlot(1).ch3.coordinate,...
    voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate]);