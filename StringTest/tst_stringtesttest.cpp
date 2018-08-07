#include <QString>
#include <QtTest>

class StringTestTest : public QObject
{
    Q_OBJECT

public:
    StringTestTest();

private Q_SLOTS:
    void toUpper();
};

StringTestTest::StringTestTest()
{

}


//QTEXT_APPLESS_MAIN(StringTestTest)
//#include "tst_stringtesttest.moc"

void StringTestTest::toUpper()
{
    QString str="text";
    QVERIFY2(true,"Failure");
    QCOMPARE(str.toUpper(),QString("TEXT"));
}

QTEST_APPLESS_MAIN(StringTestTest)

#include "tst_stringtesttest.moc"
