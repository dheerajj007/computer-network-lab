window.onload = function () {
  const form = document.getElementById("featureForm");
  form.addEventListener("submit", function (event) {
    event.preventDefault(); // Prevent form submission

    const accountInputs = document.getElementsByClassName("accountInput");
    const accounts = [];

    // Iterate over each account input and capture the values
    for (let i = 0; i < accountInputs.length; i++) {
      const accountBranch = accountInputs[i].querySelector(
        'input[name="accountBranch"]'
      ).value;
      const accountID = accountInputs[i].querySelector(
        'input[name="accountID"]'
      ).value;
      const cycleDetails = {
        monthly: accountInputs[i].querySelector('input[name="monthly"]')
          .checked,
        daily: accountInputs[i].querySelector('input[name="daily"]').checked,
        weekly: accountInputs[i].querySelector('input[name="weekly"]').checked,
      };
      const flag1 = accountInputs[i].querySelector(
        'input[name="flag1"]'
      ).checked;
      const flag2 = accountInputs[i].querySelector(
        'input[name="flag2"]'
      ).checked;

      accounts.push({
        accountBranch: accountBranch,
        accountID: accountID,
        cycleDetails: cycleDetails,
        flag1: flag1,
        flag2: flag2,
      });
    }

    // Generate the feature file content based on the inputs
    const featureFileContent = generateFeatureFileContent(accounts);

    // Download the generated feature file
    downloadFeatureFile(featureFileContent);
  });

  const addAccountButton = document.getElementById("addAccountButton");
  addAccountButton.addEventListener("click", function () {
    const accountInputs = document.getElementById("accountInputs");
    const accountInput = document.createElement("div");
    accountInput.className = "accountInput";

    const accountCount =
      document.getElementsByClassName("accountInput").length + 1;

    accountInput.innerHTML = `
            <h3>Account Details ${accountCount}</h3>
            <label for="accountBranch">Account Branch:</label>
            <input type="text" name="accountBranch" required><br><br>

            <label for="accountID">Account ID:</label>
            <input type="text" name="accountID" required><br><br>

            <label for="cycleDetails">Cycle Details:</label>
            <input type="checkbox" name="monthly"> Monthly
            <input type="checkbox" name="daily"> Daily
            <input type="checkbox" name="weekly"> Weekly<br><br>

            <label for="flag1">Flag 1:</label>
            <input type="checkbox" name="flag1"><br><br>

            <label for="flag2">Flag 2:</label>
            <input type="checkbox" name="flag2"><br><br>
        `;

    accountInputs.appendChild(accountInput);
  });

  function generateFeatureFileContent(accounts) {
    let content = "";

    content += "Feature: Account Management\n\n";
    content += `Scenario: Account Creation\n\n`;

    for (let i = 0; i < accounts.length; i++) {
      const account = accounts[i];

      content += `  Given I have the following account details:\n`;
      content += `    | Branch | ${account.accountBranch} |\n`;
      content += `    | ID     | ${account.accountID} |\n`;
      content += `    | Cycle Details | ${getCycleDetails(
        account.cycleDetails
      )} |\n`;
      content += `    | Flag 1 | ${account.flag1} |\n`;
      content += `    | Flag 2 | ${account.flag2} |\n\n`;
      content += `  When I initiate the account creation\n`;
      content += `  Then the account should be created successfully\n\n`;
    }

    return content;
  }

  function getCycleDetails(cycleDetails) {
    let details = "";

    if (cycleDetails.monthly) {
      details += "Monthly ";
    }

    if (cycleDetails.daily) {
      details += "Daily ";
    }

    if (cycleDetails.weekly) {
      details += "Weekly";
    }

    return details.trim();
  }

  function downloadFeatureFile(content) {
    const fileName = "GeneratedFeature.feature";
    const element = document.createElement("a");
    element.setAttribute(
      "href",
      "data:text/plain;charset=utf-8," + encodeURIComponent(content)
    );
    element.setAttribute("download", fileName);
    element.style.display = "none";
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);
  }
};
