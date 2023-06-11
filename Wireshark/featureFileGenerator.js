function generateFeatureFile(accounts) {
  let featureFileContent = "Feature: Account Details\n";
  const accountArray = Object.values(accounts);

  accountArray.forEach((account, index) => {
    const { branch, accountId, cycleFrequency, startDate, endDate } = account;
    const profileName = cycleFrequency + "-" + branch;

    featureFileContent += `Scenario: Account ${index + 1} - ${accountId}\n`;
    featureFileContent += `  Given the account details\n`;
    featureFileContent += `    | Branch          | ${branch}         |\n`;
    featureFileContent += `    | Account ID      | ${accountId}      |\n`;
    featureFileContent += `    | Profile Name    | ${profileName}       |\n`;
    featureFileContent += `    | Cycle Frequency | ${cycleFrequency} |\n`;
    featureFileContent += `    | Start Date      | ${startDate}      |\n`;
    featureFileContent += `    | End Date        | ${endDate}        |\n\n`;
  });

  return featureFileContent;
}

module.exports = { generateFeatureFile };
