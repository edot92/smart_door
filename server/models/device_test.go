package models

import (
	"fmt"
	"log"
	"testing"

	"gitlab.com/edot92/sukron-smart_door/server/engine"
)

func Test_GetHistoryDateRange(t *testing.T) {
	engine.BukaDatabase()
	param := Paramhistorydate{
		"2016-08-20 12:00:00.000000000",
		"2018-08-04 12:00:00.000000000",
	}
	rows, err := engine.KonDB.Debug().DB().Query("SELECT id FROM 'data_serial_dbs'  WHERE (created_at >= '" + param.StartDate + "' AND created_at <= '" + param.EndDate + "')")
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()
	for rows.Next() {
		var id int
		err = rows.Scan(&id)
		if err != nil {
			log.Fatal(err)
		}
		fmt.Println(id)
	}
	err = rows.Err()
	if err != nil {
		log.Fatal(err)
	}
	// var result []engine.DataSerialDB
	// // // log.Fatal(time.Parse(time.RFC3339, param.StartDate))
	// strSQL := " SELECT * FROM 'data_serial_dbs'  WHERE (created_at >= ? AND created_at <= ?)"
	// engine.KonDB.Debug().Raw(strSQL, param.StartDate, param.EndDate).Scan(&result)
	// fmt.Println(result)

	// rows, err := engine.KonDB.DB().Query(strSQL, param.StartDate, param.EndDate)
	// if err != nil {
	// 	log.Fatal(err)
	// }
	// fmt.Println(rows)
	// defer rows.Close()
	// for rows.Next() {
	// 	var id int
	// 	err := rows.Scan(id)
	// 	if err != nil {
	// 		log.Fatal(err)
	// 	}
	// 	fmt.Println("id=")
	// 	fmt.Println(id)
	// }
	// fmt.Println(res)
	// err = rows.Err()
	// fmt.Println(err)
	// var result []engine.DataSerialDB
	// strSql := "SELECT * FROM 'data_serial_dbs'  WHERE (created_at BETWEEN ? AND?)"

	// t.Log(res)
}
