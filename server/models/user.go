package models

import (
	"errors"
	"strings"
	"time"

	"github.com/edot92/smart_door/server/engine"
	"github.com/metakeule/fmtdate"
)

func Addnewuser(paramUsername, paramPassword string) error {
	date := fmtdate.Format("YYYY-MM-DD hh:mm:ss", time.Now())
	date = date + ".000000000+07:00"
	var tempRes engine.DBUser
	err := engine.KonDB.First(&tempRes, "username=?", paramUsername).Error
	if err != nil {
		if strings.Contains(err.Error(), "record not found") {
			var paramSave = engine.DBUser{
				Username:  paramUsername,
				Password:  paramPassword,
				Role:      "",
				CreatedAt: date,
				UpdateAt:  date,
			}
			err := engine.KonDB.Create(&paramSave).Error
			return err
		}
		return err
	}
	return errors.New(" username sudah ada")
}
func Getalluser() ([]engine.DBUser, error) {
	var res []engine.DBUser
	err := engine.KonDB.Find(&res).Error
	return res, err
}

func Deleteuserbyid(paramID int) error {
	var tempRes engine.DBUser
	err := engine.KonDB.First(&tempRes, "id=?", paramID).Error
	if err != nil {
		return err
	}
	err = engine.KonDB.Delete(&tempRes).Error
	return err
}

func Login(paramUsername, paramPassword string) (engine.DBUser, error) {
	var tempRes engine.DBUser
	err := engine.KonDB.First(&tempRes, "username=? and password=?", paramUsername, paramPassword).Error
	return tempRes, err
}
