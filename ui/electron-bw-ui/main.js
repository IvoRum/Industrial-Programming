const { app, BrowserWindow } = require("electron");

const createWindow = () => {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
  });

  win.loadFile("index.html");
};
const { ipcMain } = require("electron");

// This will receive the variable from the renderer process
ipcMain.on("setGlobalVariable", (event, variableValue) => {
  let name = "Nathan";
  document.getElementById("name").innerHTML = name;
});

app.whenReady().then(() => {
  createWindow();
});
