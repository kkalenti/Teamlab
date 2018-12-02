% --- Создается пустая цель гипотезы
function makeEmptyHypo()
    Hypo.x = [];
    Hypo.y = [];
    Hypo.z = [];
    Hypo.Vx = [];
    Hypo.Vy = [];
    Hypo.Vz = [];
    Hypo.ax = [];
    Hypo.ay = [];
    Hypo.az = [];
    Hypo.t = [];
    assignin('base','Hypo',Hypo);
   