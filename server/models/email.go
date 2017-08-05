package models

import (
	"errors"
	"strings"
	"time"

	"github.com/edot92/smart_door/server/engine"
	"github.com/metakeule/fmtdate"
)

func Addnewemail(paramNama, paramEmail string) error {
	date := fmtdate.Format("YYYY-MM-DD hh:mm:ss", time.Now())
	date = date + ".000000000+07:00"
	var tempRes engine.DBEmail
	err := engine.KonDB.First(&tempRes, "email=?", paramEmail).Error
	if err != nil {
		if strings.Contains(err.Error(), "record not found") {
			var paramSave = engine.DBEmail{
				Nama_lengkap: paramNama,
				Email:        paramEmail,
				CreatedAt:    date,
				UpdateAt:     date,
			}
			err := engine.KonDB.Create(&paramSave).Error
			return err
		}
		return err
	}
	return errors.New("alamat email sudah ada")
}
func Getallemail() ([]engine.DBEmail, error) {
	var res []engine.DBEmail
	err := engine.KonDB.Find(&res).Error
	return res, err
}

func Deleteemailbyid(paramID int) error {
	var tempRes engine.DBEmail
	err := engine.KonDB.First(&tempRes, "id=?", paramID).Error
	if err != nil {
		return err
	}
	err = engine.KonDB.Delete(&tempRes).Error
	return err
}
