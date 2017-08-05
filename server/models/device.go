package models

import "github.com/edot92/smart_door/server/engine"

type ParamChart struct {
	JenisChart string `json:"jenis_chart"`
}
type ResponChart struct {
	Value float32 `json:"value"`
	Time  string  `json:"time"`
}
type Paramhistorydate struct {
	Startdate string `json:"startdate"`
	Enddate   string `json:"enddate"`
}

// Getlastvalue ...
func Getlastvalue() (engine.DBAlat, error) {
	var res engine.DBAlat
	err := engine.KonDB.Where("id=?", 1).First(&res).Error
	return res, err
}

// Updatevalue ...
func Updatevalue(paramDoor string) error {
	err := engine.KonDB.Table("db_alats").Where("id=?", 1).Update("control_door"+paramDoor, "1").Error
	return err
}

// func GetRealtimeChart(jenisChart string) ([]ResponChart, error) {
//
// }

// func GetHistoryDateRange(param Paramhistorydate) ([]engine.DataSerialDB, error) {
// 	var res []engine.DataSerialDB
// 	// param.Startdate = "2016-01-24T12:00:00.000000000+07:00"
// 	// param.Enddate = "2019-01-24T12:00:00.000000000+07:00"
// 	// err := engine.KonDB.Debug().Where("created_at >= ? AND created_at <=?", param.Startdate, param.Enddate).Find(&res).Error
// 	err := engine.KonDB.Debug().Where(" created_at BETWEEN  (?) AND (?) ", param.Startdate, param.Enddate).Find(&res).Error
//
// 	if err != nil {
// 		log.Fatal(err)
// 	}
// 	return res, nil
//
// }
