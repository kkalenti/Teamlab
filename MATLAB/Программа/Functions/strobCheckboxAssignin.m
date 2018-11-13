% --- Создание графиков и привязка их к определенным чекбоксам для
% данных строба
function strobCheckboxAssignin(Strob)
strob.ch13 = errorbar(Strob.t(:),Strob.x(:),Strob.Sx(:),...
    'og','Visible','off','DisplayName', 'Стробы по x');
strob.ch14 = errorbar(Strob.t(:),Strob.y(:),Strob.Sy(:),...
    'or','Visible','off','DisplayName', 'Стробы по y');
strob.ch15 = errorbar(Strob.t(:),Strob.z(:),Strob.Sz(:),...
    'ob','Visible','off','DisplayName', 'Стробы по z');

assignin('base','strobPlot',strob);