#ifndef QUERYSTRING_H
#define QUERYSTRING_H
#include <database.h>

const static QString EOLine = QString("\n");
const static QString EOField = QString(",") + EOLine;
const static QString EOExpr = QString(";");
const static QString SETISODATE = QString("set datestyle to 'ISO,MDY'");
const static QString SELECT = SETISODATE + ";" + "SELECT";
const static QString LICENSE_NOTEXPIRED = QString("(purchase.expires > current_date)");
const static QString LICENSE_EXPIRED = QString("(purchase.expires < current_date)");
const static QString LICENSE_ACTIVATED = QString("((purchase.expires - purchase.activated) > '3 days')");
const static QString LICENSEVALID = LICENSE_ACTIVATED + " AND " +  LICENSE_NOTEXPIRED;

static QStringList id_headers = QStringList()
        << "user_id"
        << "account_id"
        << "bundle_id"
        << "purchase_id"
        << "license_id"
        << "update_id"
        << "charge_id"
        << "history_id"
        << "renewal_id"
        << "license_type";

//===============================================================================
// SELECT STRINGS
//===============================================================================

const static QString accountSelectString = QString()
        + "account.owner AS User_ID" + EOField
        + "account.id AS Account_ID" + EOField
        + "account.email AS Account_Email" + EOField
        + "account.credit AS Account_Credit"
        ;

const static QString bundleSelectString = QString()
        + "bundle.id AS Bundle_ID" + EOField
        + "bundle.sku AS SKU" + EOField
        + "bundle.cost_per_period AS Renewal_Amount" + EOField
        + "bundle.period AS Renewal_Period" + EOField
        + "bundle.next_charge AS Next_Renewal_Date"
        ;

const static QString purchaseSelectString = QString()
        + "purchase.id AS Purchase_ID" + EOField
        + "purchase.renews AS Renews" + EOField
        + "purchase.assignee AS License_Assignee" + EOField
        + "purchase.activated AS License_Activated" + EOField
        + "purchase.expires AS License_Expires"
        ;

const static QString purchasedLicenseSelectString = QString()
        + "purchased_license.id AS License_ID" + EOField
        + "purchased_license.type AS License_Type"
        ;

const static QString oneTimeChargeSelectString = QString()
        + "one_time_charge.id AS Charge_ID" + EOField
        + "one_time_charge.amount AS Charge_Amount" + EOField
        + "one_time_charge.created AS Charge_Created" + EOField
        + "one_time_charge.completed AS Charge_Completed" + EOField
        + "one_time_charge.attempts AS Charge_Attempts"
        ;

const static QString oneTimeUpdateSelectString = QString()
        + "one_time_update.id AS Update_ID"
        ;

const static QString purchaseHistorySelectString = QString()
        + "purchase_history.id AS History_ID" + EOField
        + "purchase_history.sku AS History_SKU" + EOField
        + "purchase_history.quantity AS History_Quantity" + EOField
        + "purchase_history.amount AS History_Amount"
        ;

const static QString renewalHistorySelectString = QString()
        + "renewal_history.id AS Renewal_ID" + EOField
        + "renewal_history.timestamp AS Renewal_Timestamp" + EOField
        + "renewal_history.renews AS Renewal_Renews"
        ;

const static QString freeLicenseSelectString = QString()
        + "free_license.id AS License_ID" + EOField
        + "free_license.type AS Type" + EOField
        + "free_license.granted AS Activated"
        ;
const static QString userSelectString = QString()
        + "fp_user.id AS Owner" + EOField
        + "fp_user.email AS Email" + EOField
        + "profile.normalized_handle AS Username" + EOField
        + "profile.display AS Full_Name" + EOField
        + "profile.company AS Company" + EOField
//        + "count(project.author) AS Projects" + EOField
//        + "min(login.when) AS Sign_On_Date" + EOField
//        + "min(project.created) AS First_Created" + EOField
        + "max(project.created) AS Last_Modified" + EOLine
        ;

const static QString salesforceSelectString = QString()
//      + "salesforce.salesforce_id AS Salesforce_ID"
        ;

const static QString subscriptionSelectString = QString()
        + "subscription.id AS Sub_ID" + EOField
        + "subscription.token AS Token" + EOField
        + "subscription.active AS Active" + EOLine
        ;

//================================================================================
// QUERY STRINGS
//================================================================================


const static QString licenseQueryString =
        SELECT + EOLine
        + accountSelectString + EOField
        + bundleSelectString + EOField
        + purchaseSelectString + EOField
        + purchasedLicenseSelectString + EOLine

        + "FROM public.account AS account" + EOLine         // ACCOUNT

        + "LEFT JOIN public.bundle AS bundle" + EOLine        // BUNDLE
        + "ON bundle.owner = account.id" + EOLine

        + "LEFT JOIN public.purchase AS purchase" + EOLine     // PURCHASE
        + "ON purchase.bundle = bundle.id" + EOLine

        + "LEFT JOIN public.purchased_license AS purchased_license" + EOLine // PURCHASE LICENSE
        + "ON purchased_license.purchase = purchase.id" + EOLine

        ;


const static QString DetailQueryString =
        SELECT + EOLine
        + accountSelectString + EOField
        + bundleSelectString + EOField
        + purchaseSelectString + EOField
        + purchasedLicenseSelectString + EOField
        + oneTimeUpdateSelectString + EOField
        + oneTimeChargeSelectString + EOField
        + purchaseHistorySelectString + EOField
        + renewalHistorySelectString + EOField
        + subscriptionSelectString + EOLine

        + "FROM public.account AS account" + EOLine         // ACCOUNT

        + "LEFT JOIN public.bundle AS bundle" + EOLine        // BUNDLE
        + "ON bundle.owner = account.id" + EOLine

        + "LEFT JOIN public.purchase AS purchase" + EOLine     // PURCHASE
        + "ON purchase.bundle = bundle.id" + EOLine

        + "LEFT JOIN public.purchased_license AS purchased_license" + EOLine // PURCHASE LICENSE
        + "ON purchased_license.purchase = purchase.id" + EOLine

        + "LEFT JOIN public.one_time_update AS one_time_update" + EOLine     // PURCHASE
        + "ON one_time_update.purchase = purchase.id" + EOLine

        + "LEFT JOIN public.one_time_charge AS one_time_charge" + EOLine     // PURCHASE
        + "ON one_time_charge.id = one_time_update.charge" + EOLine

        + "LEFT JOIN public.renewal_history AS renewal_history" + EOLine     // PURCHASE
        + "ON renewal_history.purchase = purchase.id" + EOLine

        + "LEFT JOIN public.purchase_history AS purchase_history" + EOLine     // PURCHASE
        + "ON purchase_history.bundle = bundle.id" + EOLine

        + "LEFT JOIN public.subscription AS subscription" + EOLine     // PURCHASE
        + "ON account.id = subscription.account" + EOLine

        ;

const static QString fullQueryString =
        SELECT + EOLine
        + accountSelectString + EOField
        + bundleSelectString + EOField
        + purchaseSelectString + EOField
        + LICENSE_ACTIVATED + "AS Was_Activated" + EOField
        + purchasedLicenseSelectString + EOLine

        + "FROM public.account AS account" + EOLine         // ACCOUNT

        + "LEFT JOIN public.bundle AS bundle" + EOLine        // BUNDLE
        + "ON bundle.owner = account.id" + EOLine

        + "LEFT JOIN public.purchase AS purchase" + EOLine     // PURCHASE
        + "ON purchase.bundle = bundle.id" + EOLine

        + "LEFT JOIN public.purchased_license AS purchased_license" + EOLine // PURCHASE LICENSE
        + "ON purchased_license.purchase = purchase.id" + EOLine
        ;

const static QString trialQueryString =
        SELECT + EOLine
        + accountSelectString + EOField

        + "trial_signup.id AS Trial_ID" + EOField
        + "trial_signup.type AS Type" + EOField
        + "trial_signup.activated AS Activated" + EOField
        + "trial_signup.expires AS Expires"+ EOLine

        + "FROM public.trial_signup AS trial_signup"+ EOLine
        + "LEFT OUTER JOIN public.account AS account"+ EOLine
        + "ON trial_signup.owner = account.id"+ EOLine
        ;

const static QString freeQueryString =
        SELECT + EOLine
        + accountSelectString + EOField
        + freeLicenseSelectString + EOLine

        + "FROM public.free_license AS free_license" + EOLine
        + "LEFT OUTER JOIN public.account AS account" + EOLine
        + "ON account.owner = free_license.assignee" + EOLine
        ;

const static QString purchaseQueryString =
        SELECT + EOLine
        + accountSelectString + EOField
        + bundleSelectString + EOField
        + purchaseSelectString + EOField
        + LICENSE_ACTIVATED + " AS Was_Activated" + EOField
        + purchasedLicenseSelectString + EOLine

        + "FROM public.bundle AS bundle" + EOLine

        + "LEFT JOIN public.account AS account" + EOLine
        + "ON bundle.owner = account.id" + EOLine

        + "LEFT JOIN public.purchase AS purchase" + EOLine
        + "ON purchase.bundle = bundle.id" + EOLine

        + "LEFT JOIN public.purchased_license AS purchased_license" + EOLine // PURCHASE LICENSE
        + "ON purchased_license.purchase = purchase.id" + EOLine

//        + "WHERE " + LICENSE_ACTIVATED + "AND position ('ide' in purchased_License.type) > 0" + EOLine
        ;

const static QString userQueryString =
        SELECT + EOLine
        + userSelectString + EOLine

        + "FROM public.\"user\" AS fp_user" + EOLine

        + "LEFT JOIN public.profile AS profile" + EOLine
        + "ON fp_user.id=profile.\"user\"" + EOLine

        + "LEFT JOIN public.project AS project" + EOLine
        + "ON fp_user.id=project.author" + EOLine

        + "LEFT JOIN public.login AS login" + EOLine
        + "ON fp_user.id=login.\"user\"" + EOLine

        + "WHERE fp_user.verified = TRUE AND CHAR_LENGTH(profile.normalized_handle) <> 0" + EOLine
        + "GROUP BY fp_user.id, profile.normalized_handle, profile.display, profile.company" + EOLine
        ;

const static QString subscriptionQuery =
        SELECT + EOLine
        + subscriptionSelectString + EOLine
        + "FROM public.subscription AS subscription" + EOLine

        + "INNER JOIN public.account as account" + EOLine
        + "ON subscription.account=account.id" + EOLine
        ;

const static QString oneTimeChargeQueryString =
        SELECT + EOLine
        + "account.owner AS fp_user" + EOField
        + oneTimeChargeSelectString + EOLine

        + "FROM public.one_time_charge AS one_time_charge" + EOLine

        + "LEFT JOIN public.account AS account" + EOLine
        + "ON one_time_charge.owner=account.id" + EOLine
        ;

const static QString renewalHistoryQueryString =
        SELECT + EOLine
        + "account.owner AS fp_user" + EOField
        + oneTimeChargeSelectString + EOLine

        + "FROM public.one_time_charge AS one_time_charge" + EOLine

        + "LEFT JOIN public.account AS account" + EOLine
        + "ON one_time_charge.owner=account.id" + EOLine
        ;



#endif // QUERYSTRING_H
