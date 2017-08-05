package engine

import (
	"log"
	"time"

	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/sqlite"
	"github.com/metakeule/fmtdate"
)

//  KonDB ....
var KonDB *gorm.DB

type DataSerialDB struct {
	ID           uint64 `json:"id" gorm:"primary_key"`
	StatusDoor1  string `json:"status_door1"`
	StatusDoor2  string `json:"status_door2"`
	ControlDoor1 string `json:"control_door1"`
	ControlDoor2 string `json:"control_door2"`
	CreatedAt    string `json:"created_at"`
	UpdateAt     string `json:"update_at"`
}

type DBAlat struct {
	ID           int    `json:"id" gorm:"primary_key"`
	StatusDoor1  string `json:"status_door1"`
	StatusDoor2  string `json:"status_door2"`
	ControlDoor1 string `json:"control_door1"`
	ControlDoor2 string `json:"control_door2"`
	CreatedAt    string `json:"created_at"`
	UpdateAt     string `json:"update_at"`
}
type DBUser struct {
	ID        int    `json:"id" gorm:"primary_key"`
	Username  string `json:"username"`
	Password  string `json:"password"`
	Role      string `json:"role"`
	CreatedAt string `json:"created_at"`
	UpdateAt  string `json:"update_at"`
}
type DBLog struct {
	ID        int    `json:"id" gorm:"primary_key"`
	Jenis     string `json:"jenis"` //masuk,keluar,darurat/
	CreatedAt string `json:"created_at"`
	UpdateAt  string `json:"update_at"`
}
type DBLogAlat struct {
	ID        int    `json:"id" gorm:"primary_key"`
	Jenis     string `json:"jenis"` //masuk,keluar,darurat/
	CreatedAt string `json:"created_at"`
	UpdateAt  string `json:"update_at"`
}
type DBLogUser struct {
	ID        int    `json:"id" gorm:"primary_key"`
	Jenis     string `json:"jenis"` //masuk,keluar,darurat/
	CreatedAt string `json:"created_at"`
	UpdateAt  string `json:"update_at"`
}
type DBEmail struct {
	ID           int    `json:"id" gorm:"primary_key"`
	Nama_lengkap string `json:"nama_lengkap"` //masuk,keluar,darurat/
	Email        string `json:"email"`        //masuk,keluar,darurat/
	CreatedAt    string `json:"created_at"`
	UpdateAt     string `json:"update_at"`
}

// BukaDatabase ..
func BukaDatabase() error {
	db, err := gorm.Open("sqlite3", "smart_door.db")
	if err != nil {
		return err
	}
	db.LogMode(true)
	if db.HasTable(&DBUser{}) == false {
		db.AutoMigrate(&DBUser{})
	}

	if db.HasTable(&DBLogAlat{}) == false {
		db.AutoMigrate(&DBLogAlat{})
	}
	if db.HasTable(&DBLogUser{}) == false {
		db.AutoMigrate(&DBLogUser{})
	}
	if db.HasTable(&DBEmail{}) == false {
		db.AutoMigrate(&DBEmail{})
	}
	if db.HasTable(&DBAlat{}) == false {
		date := fmtdate.Format("YYYY-MM-DD hh:mm:ss", time.Now())
		date = date + ".000000000+07:00"
		db.AutoMigrate(&DBAlat{})
		param := DBAlat{
			ID:           1,
			StatusDoor1:  "0",
			StatusDoor2:  "0",
			ControlDoor1: "0",
			ControlDoor2: "0",
			CreatedAt:    date,
			UpdateAt:     date}
		err := db.Create(param).Error
		if err != nil {
			log.Fatal(err)
		}
	}
	KonDB = db
	return nil
}
