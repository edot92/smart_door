package models

import (
	"time"

	"github.com/edot92/smart_door/server/engine"
	"github.com/metakeule/fmtdate"
)

func init() {
}

func Updateclosealldoor(paramDoor string) error {
	err := engine.KonDB.Table("db_alats").Where("id=?", 1).Update("control_door"+paramDoor, "0").Error
	return err
}
func UpdatelogAlat(paramJenis string) error {
	date := fmtdate.Format("YYYY-MM-DD hh:mm:ss", time.Now())
	date = date + ".000000000+07:00"
	var paramSave = engine.DBLogAlat{
		Jenis:     paramJenis,
		CreatedAt: date,
		UpdateAt:  date,
	}
	err := engine.KonDB.Create(&paramSave).Error
	return err
}
