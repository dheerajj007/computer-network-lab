const express = require("express");
const app = express();
const path = require("path");
const featureFileGenerator = require("./featureFileGenerator");

app.set("view engine", "ejs");
app.use(express.urlencoded({ extended: true }));
// app.use(express.static(path.join(__dirname, "public")));

app.get("/", (req, res) => {
  res.render("index");
});

app.post("/generate", (req, res) => {
  const { branch, accountId, cycleFrequency, startDate, endDate } = req.body;
  const accounts = [];

  // Prepare the accounts array
  for (let i = 0; i < branch.length; i++) {
    const account = {
      branch: branch[i],
      accountId: accountId[i],
      cycleFrequency: cycleFrequency[i],
      startDate: startDate[i],
      endDate: endDate[i],
    };
    accounts.push(account);
  }

  const featureFileContent = featureFileGenerator.generateFeatureFile(accounts);

  res.set("Content-Disposition", "attachment; filename=featureFile.feature");
  res.send(featureFileContent);
});

app.listen(3000, () => {
  console.log("Server is running on port 3000");
});
