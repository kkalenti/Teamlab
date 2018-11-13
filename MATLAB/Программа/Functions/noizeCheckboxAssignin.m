% --- Создание графиков и привязка их к определенным чекбоксам для
% данных Шумов
function noizeCheckboxAssignin(Noize)
noize.ch9 = plot(Noize.t(:),Noize.x(:),':g','Visible','off','DisplayName', 'Шумы по x');
noize.ch10 = plot(Noize.t(:),Noize.y(:),':r','Visible','off','DisplayName', 'Шумы по y');
noize.ch11 = plot(Noize.t(:),Noize.z(:),':b','Visible','off','DisplayName', 'Шумы по z');

assignin('base','noizePlot',noize);
