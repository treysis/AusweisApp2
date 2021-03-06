/*
 * \copyright Copyright (c) 2016-2020 Governikus GmbH & Co. KG, Germany
 */

import QtQuick 2.12

import Governikus.Global 1.0
import Governikus.Style 1.0
import Governikus.Provider 1.0
import Governikus.TitleBar 1.0
import Governikus.View 1.0
import Governikus.Type.AuthModel 1.0
import Governikus.Type.NumberModel 1.0
import Governikus.Type.CertificateDescriptionModel 1.0
import Governikus.Type.ChatModel 1.0


SectionPage {
	id: baseItem

	navigationAction: NavigationAction {
			state: "cancel"
			onClicked: AuthModel.cancelWorkflow()
		}
	//: LABEL ANDROID_TABLET IOS_TABLET
	title: qsTr("Identify")

	content: Column {
		width: baseItem.width
		padding: Constants.pane_padding

		Column {
			width: parent.width - 2 * Constants.pane_padding
			spacing: Constants.pane_spacing

			GText {
				width: parent.width

				//: LABEL ANDROID_TABLET IOS_TABLET
				text: qsTr("You are about to identify yourself towards the following provider:")
			}

			GPane {
				anchors {
					left: parent.left
					right: parent.right
				}

				color: mouseArea.pressed ? Style.color.background_pane_active : Style.color.background_pane

				Item {
					width: parent.width
					height: providerEntries.height

					Accessible.description: qsTr("Click for more information about the provider")
					Accessible.onPressAction: mouseArea.clicked(null)

					Column {
						id: providerEntries
						anchors.top: parent.top
						anchors.left: parent.left
						anchors.right: confirmButton.left
						spacing: Constants.pane_spacing

						ProviderInfoSection {
							imageSource: "qrc:///images/provider/information.svg"
							//: LABEL ANDROID_TABLET IOS_TABLET
							title: qsTr("Provider")
							name: CertificateDescriptionModel.subjectName
						}
						ProviderInfoSection {
							imageSource: "qrc:///images/provider/purpose.svg"
							//: LABEL ANDROID_TABLET IOS_TABLET
							title: qsTr("Purpose for reading out requested data")
							name: CertificateDescriptionModel.purpose
						}
					}

					TintableIcon {
						id: forwardAction

						anchors.right: parent.right
						anchors.verticalCenter: parent.verticalCenter

						sourceSize.height: Style.dimens.small_icon_size
						source: "qrc:///images/mobile/material_arrow_right.svg"
						tintColor: Style.color.secondary_text
					}

					MouseArea {
						id: mouseArea

						anchors.fill: parent

						onClicked: firePush(certificateDescriptionPage)
					}

					GButton {
						id: confirmButton

						anchors.right: forwardAction.left
						anchors.verticalCenter: parent.verticalCenter
						anchors.margins: Constants.component_spacing

						//: LABEL ANDROID_TABLET IOS_TABLET %1 can be "CAN" or "PIN"
						text: qsTr("Proceed to %1 entry").arg(
																NumberModel.isCanAllowedMode ?
																//: LABEL ANDROID_TABLET IOS_TABLET  Inserted into "Proceed to %1 entry"
																qsTr("CAN") :
																//: LABEL ANDROID_TABLET IOS_TABLET Inserted into "Proceed to %1 entry"
																qsTr("PIN")
															)

						icon.source: "qrc:///images/identify.svg"
						tintIcon: true

						onClicked: {
							ChatModel.transferAccessRights()
							AuthModel.continueWorkflow()
						}
					}

					Component {
						id: certificateDescriptionPage

						CertificateDescriptionPage {
							name: CertificateDescriptionModel.subjectName
						}
					}
				}
			}

			GText {
				width: parent.width

				text: NumberModel.isCanAllowedMode
					  //: LABEL ANDROID_TABLET IOS_TABLET
					  ? qsTr("By entering the CAN, access to the following data of the ID card will be allowed to the mentioned provider:")
					  //: LABEL ANDROID_TABLET IOS_TABLET
					  : qsTr("By entering your PIN, access to the following data of your ID card will be allowed to the mentioned provider:")
			}

			GPane {
				visible: transactionInfoText.text !== "" || noDataRequestedPlaceholder.text !== ""
				anchors {
					left: parent.left
					right: parent.right
				}

				Column {
					width: parent.width

					spacing: Constants.pane_spacing

					Column {
						id: transactionInfo

						width: parent.width
						visible: transactionInfoText.text !== ""

						PaneTitle {
							height: implicitHeight * 1.5
							verticalAlignment: Text.AlignTop
							//: LABEL ANDROID_TABLET IOS_TABLET
							text: qsTr("Transactional information")
						}

						GText {
							id: transactionInfoText

							width: parent.width

							text: AuthModel.transactionInfo
							textStyle: Style.text.normal_secondary
						}
					}

					GText {
						id: noDataRequestedPlaceholder

						readonly property bool noDataRequested: !writeData.visible && !requiredData.visible && !optionalData.visible

						anchors.horizontalCenter: parent.horizontalCenter

						activeFocusOnTab: true

						//: LABEL ANDROID_TABLET IOS_TABLET
						text: noDataRequested ? qsTr("No data requested") : ""
						textStyle: Style.text.normal
					}
				}
			}

			Row {
				id: requestedDataRow

				readonly property int maxColumns: 3
				readonly property int columnWidth: (width - spacing) / maxColumns

				anchors {
					left: parent.left
					right: parent.right
				}
				height: Math.max(writeDataPane.implicitHeight, readDataPane.implicitHeight)

				spacing: Constants.pane_spacing

				GPane {
					id: writeDataPane

					visible: writeData.count > 0
					width: readDataPane.visible ? requestedDataRow.columnWidth : parent.width
					height: parent.height

					DataGroup {
						id: writeData

						width: parent.width

						onScrollPageDown: baseItem.scrollPageDown()
						onScrollPageUp: baseItem.scrollPageUp()

						//: LABEL ANDROID_TABLET IOS_TABLET
						title: qsTr("Write access (update)")
						columns: readDataPane.visible ? 1 : requestedDataRow.maxColumns
						chat: ChatModel.write
						titleStyle: Style.text.header_warning
					}
				}

				GPane {
					id: readDataPane

					visible: requiredData.count > 0 || optionalData.count > 0
					width: writeDataPane.visible ? requestedDataRow.columnWidth * 2 : parent.width
					height: parent.height

					Row {
						width: parent.width

						spacing: Constants.pane_spacing

						DataGroup {
							id: requiredData

							width: optionalData.visible ? parent.width / 2 : parent.width

							onScrollPageDown: baseItem.scrollPageDown()
							onScrollPageUp: baseItem.scrollPageUp()

							//: LABEL ANDROID_TABLET IOS_TABLET
							title: qsTr("Read access")
							columns: Math.max(1, requestedDataRow.maxColumns - (writeData.visible ? writeData.columns : 0) - (optionalData.visible ? 1 : 0) - (count > optionalData.count ? 0 : 1))
							chat: ChatModel.required
						}

						DataGroup {
							id: optionalData

							width: requiredData.visible ? parent.width / 2 : parent.width

							onScrollPageDown: baseItem.scrollPageDown()
							onScrollPageUp: baseItem.scrollPageUp()

							//: LABEL ANDROID_TABLET IOS_TABLET
							title: qsTr("Read access (optional)")
							columns: Math.max(1, requestedDataRow.maxColumns - (writeData.visible ? writeData.columns : 0) - (requiredData.visible ? requiredData.columns : 0))
							chat: ChatModel.optional
						}
					}
				}
			}
		}
	}
}
