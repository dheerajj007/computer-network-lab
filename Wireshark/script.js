window.onload = function () {
  const form = document.getElementById("featureForm");
  form.addEventListener("submit", function (event) {
    event.preventDefault(); // Prevent form submission

    const accountInputs = document.getElementsByClassName("accountInput");
    const accounts = [];

    // Iterate over each account input and capture the values
    for (let i = 0; i < accountInputs.length; i++) {
      const accountName = accountInputs[i].querySelector(
        'input[name="accountName"]'
      ).value;
      const accountNumber = accountInputs[i].querySelector(
        'input[name="accountNumber"]'
      ).value;
      const accountBranch = accountInputs[i].querySelector(
        'input[name="accountBranch"]'
      ).value;

      accounts.push({
        accountName: accountName,
        accountNumber: accountNumber,
        accountBranch: accountBranch,
      });
    }

    const cycleDetails = document.getElementById("cycleDetails").value;

    // Generate the feature file content based on the inputs
    const featureFileContent = generateFeatureFileContent(
      accounts,
      cycleDetails
    );

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
            <label for="accountName">Account Name:</label>
            <input type="text" name="accountName" required><br><br>

            <label for="accountNumber">Account Number:</label>
            <input type="text" name="accountNumber" required><br><br>

            <label for="accountBranch">Account Branch:</label>
            <input type="text" name="accountBranch" required><br><br>

            <button type="button" class="removeAccountButton">Remove Account</button><br><br>
        `;

    accountInputs.appendChild(accountInput);

    const removeAccountButton = accountInput.querySelector(
      ".removeAccountButton"
    );
    removeAccountButton.addEventListener("click", function () {
      accountInputs.removeChild(accountInput);
    });
  });

  function generateFeatureFileContent(accounts, cycleDetails) {
    let content = "";

    content += "Feature: Account Management\n\n";

    for (let i = 0; i < accounts.length; i++) {
      const account = accounts[i];

      content += `  Scenario: Account Creation ${i + 1}\n`;

      // Add multiple steps for each account
      content += `    Given I have the following account details:\n`;
      content += `      | Name   | ${account.accountName} |\n`;
      content += `      | Number | ${account.accountNumber} |\n`;
      content += `      | Branch | ${account.accountBranch} |\n`;

      content += `    When I initiate the account creation\n`;
      content += `    Then the account should be created successfully\n\n`;
    }

    content += `  Scenario: Cycle Details\n`;
    content += `    Given I have the following cycle details:\n`;
    content += `      | Details | ${cycleDetails} |\n`;
    content += `    When I perform the cycle operation\n`;
    content += `    Then the operation should be successful\n`;

    return content;
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
