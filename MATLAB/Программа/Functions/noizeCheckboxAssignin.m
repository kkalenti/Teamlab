% --- �������� �������� � �������� �� � ������������ ��������� ���
% ������ �����
function noizeCheckboxAssignin(Noize)
noize.ch9 = plot(Noize.t(:),Noize.x(:),':g','Visible','off','DisplayName', '���� �� x');
noize.ch10 = plot(Noize.t(:),Noize.y(:),':r','Visible','off','DisplayName', '���� �� y');
noize.ch11 = plot(Noize.t(:),Noize.z(:),':b','Visible','off','DisplayName', '���� �� z');

assignin('base','noizePlot',noize);
