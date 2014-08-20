#ifndef DATANODE_H
#define DATANODE_H

#include <QDateTime>
#include <QList>
#include <QString>
#include <QVariant>

class DataNode
{
public:
    DataNode();
    typedef QList<DataNode> DataNodeList;

private:
    DataNodeList m_children;
    QString m_id;
    QString m_owner;
    QDateTime m_timestamp;
    QVariant m_data;
};

class AccountNode : DataNode
{
public:
    AccountNode();

private:
    QDateTime m_signOnDate;
    QString m_userName;
    QString m_email;
    int m_credit;
    unsigned int m_monthiversary;
};

class BundleNode : DataNode
{
public:
    BundleNode();
    enum ChargePeriod { Annual, Monthly };
private:
    QString m_sku;
    QDateTime m_nextCharge;
    ChargePeriod m_period;
    int m_chargePerPeriod;
};

class PurchaseNode : DataNode
{
public:
    PurchaseNode();
private:
    QString m_bundle;
    bool m_renews;
    QString m_assignee;
    bool m_activated;
    QDateTime m_expires;
};

class PurchaseLicenseNode : DataNode
{
public:
    PurchaseLicenseNode();
private:
    QString m_purchase;
    QString m_type;
};

class PurchaseHistoryNode : DataNode
{
public:
    PurchaseHistoryNode();
private:
    QString m_bundle;
    QString m_sku;
    unsigned int m_quantity;
    int m_amount;
};

class RenewalHistoryNode : DataNode
{
public:
    RenewalHistoryNode();
private:
    QString m_purchase;
    bool m_renews;
};

class OneTimeChargeNode : DataNode
{
public:
    OneTimeChargeNode();
private:
    unsigned int m_amount;
    QDateTime m_created;
    bool m_fromReoccuring;
    unsigned int m_attempts;
    QDateTime m_nextAttempt;
    QDateTime m_completed;
    QString m_completedToken;
};

class OneTimeUpdateNode : DataNode
{
public:
    OneTimeUpdateNode();
private:
    QString m_charge;
    QString m_purchase;
    unsigned int m_extraDays;

};

class SubscriptionNode : DataNode
{
public:
    SubscriptionNode();
private:
    QString m_token;
    bool m_active;
    QDateTime m_established;
};

class TransactionNode : DataNode
{
public:
    TransactionNode();
private:
    unsigned int m_amount;
};

class UserNode : DataNode
{
public:
    UserNode();
private:
    QString m_email;
    QString m_password;
    QString m_verkey;
    bool m_verified;
    bool m_needs_new_password;
    QString m_securityToken;
};

class ProfileNode : DataNode
{
public:
    ProfileNode();
private:
    QString m_handle;
    QString m_normalizedHandle;
    QString m_display;
    QString m_keyMap;
    QString m_githubAccessKey;
    QString m_sshKeyPair;
    QString m_bio;
    QString m_company;
    QString m_homePage;
    QString m_telephone;
    QString m_theme;
    QString m_fontSize;
    bool m_searchWithRegex;
    bool m_automatic;
};


#endif // DATANODE_H
