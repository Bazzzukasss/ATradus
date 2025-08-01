TEMPLATE = subdirs

SUBDIRS += \
    SerializerLib \
    AppSettingsLib \
    RequesterLib \
    TradingTerminal

AppSettingsLib.depends = SerializerLib
TradingTerminal.depends = AppSettingsLib
TradingTerminal.depends = RequesterLib