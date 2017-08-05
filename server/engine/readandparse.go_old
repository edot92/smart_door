package engine

import (
	"encoding/json"
	"errors"
	"fmt"
	"strings"
	"time"

	"github.com/goinggo/tracelog"

	serial "go.bug.st/serial.v1"
)

type DataSerial struct {
	Temperature  float32
	Humidity     float32
	Current      float32
	Shuntvoltage float32
	Busvoltage   float32
	Loadvoltage  float32
}

// {"Temperature":"0",
// "Humidity":0,
// "Busvoltage":"12.35",
// "Shuntvoltage":"0.81",
// "Loadvoltage":"12.35",
// "Current":"7.90"}

// ser serial
var PortOpen serial.Port

// var ComPilihan = "COM4"
var ComPilihan = "/dev/ttyACM0"

func init() {
	tracelog.Start(tracelog.LevelTrace)

}
func BukaPort() (bool, string, error) {

	var (
		// address  string
		baudrate int
		// databits int
	)
	ports, err := serial.GetPortsList()
	if err != nil {
		// fmt.Println(err)
	}
	if len(ports) == 0 {
		tracelog.Warning("serial_engine", "BukaPort", "No serial ports found!")
		// tracelog.Stop()
		// fmt.Println("No serial ports found!")
		// return false
		return false, ComPilihan, nil
	}

	baudrate = 9600
	// databits = 8
	// _ = databits
	config := &serial.Mode{
		BaudRate: baudrate,
		// DataBits: databits,
		Parity:   serial.NoParity,
		StopBits: serial.OneStopBit,
	}

	// var serMode serial.Mode
	// serMode.
	for _, port := range ports {
		fmt.Printf("Found port on: %v\n", port)
		// ComPilihan = port
	}
	PortOpen, err = serial.Open(ComPilihan, config)
	if err != nil {
		fmt.Println("open error")
		fmt.Println(err)
		return false, ComPilihan, err
	}
	return true, ComPilihan, nil
}

// ReadAndParse ...
func ReadAndParse() (bool, DataSerial, error) {
	var dataSerial DataSerial

	if PortOpen == nil {
		isOk, portnya, err := BukaPort()
		if isOk == false {
			time.Sleep(5 * time.Second)
			return false, dataSerial, err
		}
		_ = portnya

	}
	// defer portOpen.Close()
	var buf [100]byte
	var pesan string
bacalagi:
	n, err := PortOpen.Read(buf[:])
	if err != nil {
		return false, dataSerial, err
	}
	pesan = pesan + string(buf[:n])
	if strings.Contains(pesan, "#") == false {
		goto bacalagi
	}
	pesan = strings.Replace(pesan, "#", "", -1)
	pesan = strings.Replace(pesan, "\r", "", -1)
	pesan = strings.Replace(pesan, "\n", "", -1)
	err = json.Unmarshal([]byte(pesan), &dataSerial)
	if err != nil {
		fmt.Println(err)
		fmt.Println(pesan)

		return false, dataSerial, errors.New("failed format type ")
	}
	fmt.Println("pesan:", pesan)
	fmt.Println(dataSerial)
	err = SimpanData(dataSerial)
	fmt.Println(err)
	return true, dataSerial, nil

}
