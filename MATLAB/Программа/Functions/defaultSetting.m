% --- �������� �������������� ������ �������
function defaultSetting(handles)
set(handles.uibuttongroup1,'Visible','on');
set(handles.uibuttongroup7,'Visible','on');
set(handles.uipanel3,'Visible','on');

grid on;
hold on;
xlabel('�����, s');
ylabel('����������, m');

Real = evalin('base','Real');
VOI = evalin('base','VOI');

realCheckboxAssignin(Real(1))
voiCheckboxAssignin(VOI(1));

realPlot = evalin('base','realPlot');
voiPlot = evalin('base','voiPlot');

setListboxes(handles);

legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
    voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,],...
    '������ x','������ y','������ z','��� x','��� y','��� z' );